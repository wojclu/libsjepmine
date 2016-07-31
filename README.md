# libsjepmine
A C++ library for extracting Strong Jumping Emerging Patterns (SJEP). Used algorithm was published in the article: Hongjian Fan, Kotagiri Ramamohanarao. Fast discovery and the generalization of strong jumping emerging patterns for building compact and accurate classifiers. IEEE Transactions on Knowledge and Data Engineering, pages 721 – 737, 2006.


## How to build
```bash
git clone https://github.com/wojcickil/libsjepmine.git
cd libsjepmine
mkdir build
cd build
cmake ..
make
make install
```

## How to use
Example C++ program (file main.cpp):
```cpp
#include "SJEPExtractor.h"
#include "CpItem.h" // CpItem, CpItemset

int main()
{

// Itemsets
//
// +------+------+------+------+------+------+------+
// |  #   |a     |b     |c     |d     |e     |class |
// +------+------+------+------+------+------+------+
// |  1   |X     |      |X     |X     |X     |D1    |
// +------+------+------+------+------+------+------+
// |  2   |X     |      |      |      |      |D1    |
// +------+------+------+------+------+------+------+
// |  3   |      |X     |      |      |X     |D1    |
// +------+------+------+------+------+------+------+
// |  4   |      |X     |X     |X     |X     |D1    |
// +------+------+------+------+------+------+------+
// |  5   |X     |X     |      |      |      |D2    |
// +------+------+------+------+------+------+------+
// |  6   |      |      |X     |      |X     |D2    |
// +------+------+------+------+------+------+------+
// |  7   |X     |X     |X     |X     |      |D2    |
// +------+------+------+------+------+------+------+
// |  8   |      |      |      |X     |X     |D2    |
// +------+------+------+------+------+------+------+

  // prepare items with numerical ids
  CpItem a(0);
  CpItem b(1);
  CpItem c(2);
  CpItem d(3);
  CpItem e(4);

  // prepare itemsets
  std::shared_ptr<CpItemset> i1 = std::make_shared<CpItemset>();
  i1->push_back(a);
  i1->push_back(c);
  i1->push_back(d);
  i1->push_back(e);

  std::shared_ptr<CpItemset> i2 = std::make_shared<CpItemset>();
  i2->push_back(a);

  std::shared_ptr<CpItemset> i3 = std::make_shared<CpItemset>();
  i3->push_back(b);
  i3->push_back(e);

  std::shared_ptr<CpItemset> i4 = std::make_shared<CpItemset>();
  i4->push_back(b);
  i4->push_back(c);
  i4->push_back(d);
  i4->push_back(e);

  std::shared_ptr<CpItemset> i5 = std::make_shared<CpItemset>();
  i5->push_back(a);
  i5->push_back(b);

  std::shared_ptr<CpItemset> i6 = std::make_shared<CpItemset>();
  i6->push_back(c);
  i6->push_back(e);

  std::shared_ptr<CpItemset> i7 = std::make_shared<CpItemset>();
  i7->push_back(a);
  i7->push_back(b);
  i7->push_back(c);
  i7->push_back(d);

  std::shared_ptr<CpItemset> i8 = std::make_shared<CpItemset>();
  i8->push_back(d);
  i8->push_back(e);

  // prepare data for exactly two classes
  // each class is described by a set of itemsets
  std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > classItemsets1 =
          std::make_shared<std::vector<std::shared_ptr<CpItemset> > >();
  classItemsets1->push_back(i1);
  classItemsets1->push_back(i2);
  classItemsets1->push_back(i3);
  classItemsets1->push_back(i4);

  std::shared_ptr<std::vector<std::shared_ptr<CpItemset> > > classItemsets2 =
          std::make_shared<std::vector<std::shared_ptr<CpItemset> > >();
  classItemsets2->push_back(i5);
  classItemsets2->push_back(i6);
  classItemsets2->push_back(i7);
  classItemsets2->push_back(i8);

  std::shared_ptr<std::vector<ClassData> > classesData = std::make_shared<std::vector<ClassData> >();
  classesData->push_back(ClassData("D1", classItemsets1));
  classesData->push_back(ClassData("D2", classItemsets2));

  // create extractor, pass minimum relative support
  SJEPExtractor sjepExtractor(classesData, 0.5);

  // extract SJEPS for both classes
  std::shared_ptr<std::vector<std::vector<SJEP> > >  sjeps = sjepExtractor.extractSJEP();

  // sjeps->at(0) // SJEPs from class D2 to D1,
  // contains 2 SJEPs:
  // {b, e}, {c, d, e}

  // sjeps->at(1) // SJEPS from class D1 to D2,
  // constains 1 SJEP:
  // {a, b}
}
```

Build command:
```bash
g++ -lsjepmine main.cpp
```
