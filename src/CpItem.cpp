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

#include "CpItem.h"

#include "CpItemset.h"

float CpItem::getSupportRatio() const
{
  return supportRatio_;
}

void CpItem::setSupportRatio(float _value)
{
  supportRatio_ = _value;
}

bool CpItem::operator==(const CpItem& _otherCpItem) const
{
  return itemId_ == _otherCpItem.itemId_;
}

bool CpItem::compare(const CpItem &_first, const CpItem &_second)
{
  if(_first.supportRatio_ > _second.supportRatio_)
    {
      return true;
    }
  else if(_first.supportRatio_ == _second.supportRatio_)
    {
      return _first.getItemId() < _second.getItemId();
    }
  else // (first.supportRatio_ < second.supportRatio_)
    {
      return false;
    }
}

int CpItem::getItemId() const
{
    return itemId_;
}

void CpItem::setItemId(const int &_itemId)
{
    itemId_ = _itemId;
}

CpItem::CpItem():
    itemId_(-1),
    supportRatio_(-1) {}

CpItem::CpItem(int _itemId):
    itemId_(_itemId), supportRatio_(-1) {}

bool CpItem::isIn(const CpItem& _other) const
{
  return itemId_ == _other.getItemId();
}

bool CpItem::isIn(const CpItemset& _itemset) const
{
  bool itemFound = false;
  for(const CpItem& otherCpItem: _itemset)
    {
      if(isIn(otherCpItem))
        {
          itemFound = true;
          break;
        }
    }
  return itemFound;
}
