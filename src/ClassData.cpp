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

#include "ClassData.h"

std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > ClassData::getItemsets() const
{
    return itemsets_;
}

void ClassData::setItemsets(const std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > _itemsets)
{
    itemsets_ = _itemsets;
}

std::string ClassData::getClassName() const
{
    return className_;
}

void ClassData::setClassName(const std::string& _className)
{
    className_ = _className;
}

ClassData::ClassData(const std::string _className,
        std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > _itemsets):
    className_(_className), itemsets_(_itemsets) {}
