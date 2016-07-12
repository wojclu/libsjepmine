#ifndef CPITEMSET_H
#define CPITEMSET_H

#include <vector>

#include "CpItem.h"

class CpItemset: public std::vector<CpItem>
{
public:
    bool isIncludedIn(const CpItemset& _other);
};

#endif // CPITEMSET_H
