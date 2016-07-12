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

#ifndef CPTREE_H
#define CPTREE_H

#include <memory>

#include "../CpItemset.h"
#include "CPNodeItem.h"
#include "CPNode.h"

class CPTree
{
  std::shared_ptr<CPNode> root_;
  void recursiveInsert(std::shared_ptr<CPNode>& _pointerFromParentPtr,
                       CpItemset& _itemset,
                       const uint _itemsetClassId);
public:
  CPTree();

  void insertItemset(const CpItemset &_itemset,
                     const uint _itemsetClassId);

  /**
   * @brief mergeTree Function merges _t1's nodes into _t2, _t2 is updated,
   * _t1 remains unchanged
   *
   * @param _t1
   * @param _t2
   */
  static void mergeTree(std::shared_ptr<CPNode> _t1,
                 std::shared_ptr<CPNode> _t2);

  std::shared_ptr<CPNode> getRoot() const;
  void setRoot(const std::shared_ptr<CPNode>& _value);
};


#endif // CPTREE_H
