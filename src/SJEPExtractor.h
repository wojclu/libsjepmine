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

#ifndef SJEPEXTRACTOR_H
#define SJEPEXTRACTOR_H

#include <memory>
#include <vector>

#include "ClassData.h"
#include "SJEP.h"
#include "CPTree/CPNode.h"

class SJEPExtractor
{
  std::shared_ptr<std::vector<ClassData> > classesData_;

  const float minimumSupportThreshold_;

  float calculateSupportRatioFor(const CpItem& _item) const;

  /**
   * @brief mineTree
   * @param _treeRoot
   * @param _partialSjep
   * @param _sjepAcc
   * @return Two-element vector with SJEPs for the first (index - 0) and the second class( index - 1)
   */
  void mineTree(std::shared_ptr<CPNode> _treeRoot,
                const SJEP& _partialSjep,
                std::shared_ptr<std::vector<std::vector<SJEP> > > _sjepAcc,
                const uint _currentDepth);
public:
  SJEPExtractor(std::shared_ptr<std::vector<ClassData> > _classesData,
                float _minimumSupportThreshold);

  std::shared_ptr<std::vector<std::vector<SJEP> > > extractSJEP();
};


#endif // SJEPEXTRACTOR_H
