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

#ifndef CPITEM_H
#define CPITEM_H

#include <vector>

class CpItemset;

class CpItem
{
protected:
  int itemId_;
  float supportRatio_; // float - has infinity

public:
  CpItem();
  CpItem(int _itemId);

  bool isIn(const CpItem& _other) const;
  bool isIn(const CpItemset& _itemset) const;

  /**
   * @brief compare Itemset order form the article
   * @param first
   * @param second
   * @return
   */
  static bool compare(const CpItem& _first, const CpItem& _second);

  int getItemId() const;
  void setItemId(const int& _itemId);

  float getSupportRatio() const;
  void setSupportRatio(float _value);

  bool operator==(const CpItem& _otherCpItem) const;
};

namespace std
{
  template<>
  struct hash<CpItem>
  {
    typedef std::size_t result_type;

    result_type operator()(const CpItem& item) const
    {
      return item.getItemId();
    }
  };
}
#endif // CPITEM_H
