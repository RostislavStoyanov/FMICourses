#include <set>
#include <list>

#ifndef HW1_DOMAIN_H
#define HW1_DOMAIN_H


class Domain
{
private:
    std::set<int> values;
    char variable;

public:
    Domain(char v, int start, int end);

    Domain(const Domain& otherDomain);

    Domain&operator= (const Domain& other);

    explicit Domain(Domain* pDomain);

    int getSize();

    bool operator<(const Domain &other);

    void updateDomain(std::list<int> &newVals);

    char getVar();

    std::set<int> getDomain();
};


#endif
