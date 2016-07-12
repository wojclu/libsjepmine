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

#include "SJEP.h"

#include <cstdlib>
#include <algorithm>

SJEP::SJEP()
{

}

SJEP::SJEP(const Itemset& _itemset): vector<int>(_itemset.size())
{
  for(size_t i = 0 ; i < _itemset.size(); ++i)
    {
      this->operator [](i) = _itemset[i];
    }
}

bool SJEP::isSubsetOf(const SJEP &_other)
{
  bool isSubset = true;

  for(int myValue: *this)
    {
      std::vector<int>::const_iterator elementInOtherSjep =
              std::find(_other.begin(), _other.end(), myValue);
      if(elementInOtherSjep == _other.end())
        {
          isSubset = false;
          break;
        }
    }

  return isSubset;
}
