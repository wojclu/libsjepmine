//---------------------------------------------------------------------------//
// Copyright 2016 Lukasz Wojcicki
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//---------------------------------------------------------------------------//

#include "SJEPExtractor.h"

#include <unordered_map>
#include <limits>
#include <algorithm>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "CpItem.h"
#include "CPTree/CPTree.h"

float SJEPExtractor::calculateSupportRatioFor(const CpItem &_item) const
{
  // calculate support ratio for the item
  std::vector<float> supports(2);
  for(size_t classIdx = 0; classIdx < classesData_->size(); ++classIdx)
    {
      assert(classIdx < 2);

      std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > classItemsets =
              (classesData_->at(classIdx)).getItemsets();
      for(const std::shared_ptr<CpItemset>& cpItemset: *classItemsets)
        {
          if(_item.isIn(*cpItemset))
            {
              supports.at(classIdx) += 1;
            }
        }
    }
  supports.at(0) /= (classesData_->at(0)).getItemsets()->size();
  supports.at(1) /= (classesData_->at(1)).getItemsets()->size();

  // calculate supportRatio
  float supportRatio = 0;
  if(supports.at(0) < minimumSupportThreshold_ && supports.at(1) < minimumSupportThreshold_)
    {
      supportRatio = 0;
    }
  else if((supports.at(0) == 0 && supports.at(1) >= minimumSupportThreshold_) ||
          (supports.at(0) >= minimumSupportThreshold_ && supports.at(1) == 0))
    {
      supportRatio = std::numeric_limits<float>::infinity();
    }
  else
    {
      supportRatio = std::max(supports[0]/supports[1], supports[1]/supports[0]);
    }

  return supportRatio;
}

SJEPExtractor::SJEPExtractor(
        std::shared_ptr<std::vector<ClassData> > _classesData,
        float _minimumSupportThreshold):
  classesData_(_classesData),
  minimumSupportThreshold_(_minimumSupportThreshold)
{
    if(minimumSupportThreshold_ < 0 || minimumSupportThreshold_ > 1)
    {
        throw std::runtime_error("_minimumSupportThreshold_: wrong value");
    }

    if(_classesData->size() != 2)
    {
        throw std::runtime_error("_classesData: requred exactly 2 classes");
    }

    if(_classesData->at(0).getItemsets()->size() == 0)
    {
        throw std::runtime_error("no keys for the first class");
    }


    if(_classesData->at(1).getItemsets()->size() == 0)
    {
        throw std::runtime_error("no keys for the second class");
    }
}

std::shared_ptr<std::vector<std::vector<SJEP> > > SJEPExtractor::extractSJEP()
{
  // let D = D_1 U D_2
  std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > allItemsets =
      std::make_shared<std::vector<std::shared_ptr<CpItemset> > >();

  // sum all itemsets, remove duplicates
  for(const ClassData& classData: *classesData_)
    {
        allItemsets->insert(allItemsets->end(),
                            classData.getItemsets()->begin(),
                            classData.getItemsets()->end());
    }

  /*
   * "collect the set of items whose support ratios are more than 0, ...,
   * sort in support-ratio-descending order"
   */

  std::shared_ptr<std::unordered_map<CpItem, float> > itemToSupportRatioMap =
      std::make_shared<std::unordered_map<CpItem, float> >();
  for(const std::shared_ptr<CpItemset> itemset : *allItemsets)
    {
      for(const CpItem& item: *itemset)
        {
          // check if ratio for the item is already calculated
          if(itemToSupportRatioMap->find(item) != itemToSupportRatioMap->end())
            {
              continue;
            }

          itemToSupportRatioMap->operator [](item) = calculateSupportRatioFor(item);
        }
    }

  CPTree cpTree;

  for(size_t classIdx = 0; classIdx < classesData_->size(); ++classIdx)
    {
      assert(classIdx < 2);

      std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > classItemsets = (classesData_->at(classIdx)).getItemsets();

      for(std::shared_ptr<CpItemset>& cpItemset: *classItemsets)
        {
          // get supportRatio,  sort, then insert to the cpTree
          for(CpItem& cpItem: *cpItemset)
            {
              std::unordered_map<CpItem, float>::iterator supportRatioIt =
                      itemToSupportRatioMap->find(cpItem);
              if(supportRatioIt == itemToSupportRatioMap->end())
                {
                  throw std::runtime_error("Cannot find SupportRatio for an item");
                }
              cpItem.setSupportRatio(supportRatioIt->second);
            }
          std::sort(cpItemset->begin(), cpItemset->end(), CpItem::compare);
          cpTree.insertItemset(*cpItemset, classIdx);
        }
    }

  // CPTree created

  std::shared_ptr<CPNode> root = cpTree.getRoot();

  // mine tree
  std::shared_ptr<std::vector<std::vector<SJEP> > > sjepAcc =
      std::make_shared<std::vector<std::vector<SJEP> > >(2);
  mineTree(root, SJEP(), sjepAcc, 0);

  // remove not minimal
  for(std::vector<SJEP>& sjeps: *sjepAcc)
    {
      for(size_t to_remove = 0; to_remove < sjeps.size(); ++to_remove)
        {
          for(size_t compare_with = 0; compare_with < sjeps.size(); ++compare_with)
            {
              if(to_remove == compare_with ||
                 sjeps[compare_with].size() == 0 || sjeps[to_remove].size() == 0)
                {
                  continue;
                }
              if(sjeps[compare_with].isSubsetOf(sjeps[to_remove]))
                {
                  sjeps[to_remove].clear();
                }
            }
        }

      std::vector<SJEP>::iterator newEnd =
          std::remove_if(sjeps.begin(), sjeps.end(), [](const SJEP& sjep) {return sjep.size() == 0;});
      sjeps.erase(newEnd, sjeps.end());
    }

  // sort
  for(std::vector<SJEP>& sjeps: *sjepAcc)
    {
      for(SJEP& sjep: sjeps)
        {
          std::sort(sjep.begin(), sjep.end());
        }
    }

  return sjepAcc;
}

void SJEPExtractor::mineTree(std::shared_ptr<CPNode> _treeRoot,
                             const SJEP& _partialSjep,
                             std::shared_ptr<std::vector<std::vector<SJEP> > > _sjepAcc,
                             const uint _currentDepth)
{
  assert(_sjepAcc->size() == 2);

//  for(CpNodeItem& currentItem: _treeRoot->itemsInNode)
  for(size_t currentItemIdx = 0; currentItemIdx < _treeRoot->itemsInNode_.size(); ++currentItemIdx)
    {
      CPNodeItem& currentItemBeforeMerge = _treeRoot->itemsInNode_.at(currentItemIdx);
      // "if subtree is not empty
      if(currentItemBeforeMerge.subtree_ != nullptr)
        {
          CPTree::mergeTree(currentItemBeforeMerge.subtree_, _treeRoot);
        }
      CPNodeItem& currentItemAfterMerge = _treeRoot->itemsInNode_.at(currentItemIdx);

      SJEP updatedSjep = _partialSjep;
      // beta = alpha U T.items[i]
      updatedSjep.push_back(currentItemAfterMerge.getItemId());
      if(currentItemAfterMerge.counts_[0] == 0 &&
         currentItemAfterMerge.counts_[1] >= classesData_->at(1).getItemsets()->size()
              * minimumSupportThreshold_)
        {
          _sjepAcc->at(1).push_back(updatedSjep);
        }
      else if(currentItemAfterMerge.counts_[1] == 0 &&
              currentItemAfterMerge.counts_[0] >= classesData_->at(0).getItemsets()->size()
              * minimumSupportThreshold_)
        {
          _sjepAcc->at(0).push_back(updatedSjep);
        }
      else if(currentItemAfterMerge.subtree_ != nullptr &&
              (currentItemAfterMerge.counts_[0] >= classesData_->at(0).getItemsets()->size()
               * minimumSupportThreshold_ ||
               currentItemAfterMerge.counts_[1] >= classesData_->at(1).getItemsets()->size()
               * minimumSupportThreshold_ ))
        {
          mineTree(currentItemAfterMerge.subtree_, updatedSjep, _sjepAcc, _currentDepth + 1);
        }
      // "free subtree"
      currentItemAfterMerge.subtree_ = nullptr;
    }
}
