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

#include "CPTree.h"

#include <algorithm>

CPTree::CPTree()
{
}

void CPTree::insertItemset(const CpItemset &_itemset, const uint _itemsetClassId)
{
  CpItemset itemsetCopy = _itemset;
  recursiveInsert(root_, itemsetCopy, _itemsetClassId);
}

std::shared_ptr<CPNode> CPTree::getRoot() const
{
    return root_;
}

void CPTree::setRoot(const std::shared_ptr<CPNode>& _value)
{
    root_ = _value;
}

void CPTree::recursiveInsert(std::shared_ptr<CPNode>& _pointerFromParentPtr,
                             CpItemset &_itemset,
                             const uint _itemsetClassId)
{
  if(_pointerFromParentPtr == nullptr)
    {
      _pointerFromParentPtr = std::make_shared<CPNode>();
    }

  CpItem currentItem = _itemset.front();
  _itemset.erase(_itemset.begin());

  // find insert currentItem in the appropriate place in itemsInNode
  std::vector<CPNodeItem>::iterator foundExistingToInsert = std::find(
              _pointerFromParentPtr->itemsInNode_.begin(),
              _pointerFromParentPtr->itemsInNode_.end(),
              currentItem);

  if(foundExistingToInsert != _pointerFromParentPtr->itemsInNode_.end())
    {
      // found before inserted item
      (*foundExistingToInsert).counts_.at(_itemsetClassId)  += 1;
    }
  else
    {
      // not found
      CPNodeItem newNodeItem(currentItem);
      newNodeItem.counts_.at(_itemsetClassId) += 1;
      _pointerFromParentPtr->itemsInNode_.push_back(newNodeItem);
      std::sort(_pointerFromParentPtr->itemsInNode_.begin(),
                _pointerFromParentPtr->itemsInNode_.end(),
                CpItem::compare);
    }

  if(!_itemset.empty())
    {
      std::vector<CPNodeItem>::iterator findSubtree = std::find(
                  _pointerFromParentPtr->itemsInNode_.begin(),
                  _pointerFromParentPtr->itemsInNode_.end(),
                  currentItem);

      recursiveInsert((*findSubtree).subtree_, _itemset, _itemsetClassId);
    }
}

void CPTree::mergeTree(std::shared_ptr<CPNode> _t1, std::shared_ptr<CPNode> _t2)
{
  for(CPNodeItem& cpNodeItemFromT1: _t1->itemsInNode_)
    {
      std::vector<CPNodeItem>::iterator foundExistingItemInT2 =
              std::find(_t2->itemsInNode_.begin(),
                        _t2->itemsInNode_.end(),
                        (CpItem) cpNodeItemFromT1);

      if(foundExistingItemInT2 != _t2->itemsInNode_.end())
        {
          (*foundExistingItemInT2).counts_[0] += cpNodeItemFromT1.counts_[0];
          (*foundExistingItemInT2).counts_[1] += cpNodeItemFromT1.counts_[1];
        }
      else
        {
          CPNodeItem newNodeItem((CpItem) cpNodeItemFromT1);  // copy without children
          newNodeItem.counts_ = cpNodeItemFromT1.counts_;
          _t2->itemsInNode_.push_back(newNodeItem);

          // obey the order
          std::sort(_t2->itemsInNode_.begin(), _t2->itemsInNode_.end(), CpItem::compare);
        }

      std::vector<CPNodeItem>::iterator foundInsertedOrExistedItemInT2 =
              std::find(_t2->itemsInNode_.begin(),
                        _t2->itemsInNode_.end(),
                        (CpItem) cpNodeItemFromT1);

      if(cpNodeItemFromT1.subtree_ != nullptr)  // M
        {
          if((*foundInsertedOrExistedItemInT2).subtree_ == nullptr) // N
            {
              (*foundInsertedOrExistedItemInT2).subtree_ = std::make_shared<CPNode>();
            }

          // mergeTree(M, N);
          mergeTree(cpNodeItemFromT1.subtree_, (*foundInsertedOrExistedItemInT2).subtree_);
        }
    }
}
