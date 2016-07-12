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

#ifndef CLASSDATA_H
#define CLASSDATA_H

#include <string>
#include <memory>
#include <vector>

#include "CpItemset.h"

class ClassData
{
  std::string className_;

  std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > itemsets_;

public:
  ClassData(const std::string _className,
            std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > _itemsets);

  std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > getItemsets() const;
  void setItemsets(const std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > _itemsets);

  std::string getClassName() const;
  void setClassName(const std::string& _className);
};

#endif // CLASSDATA_H
