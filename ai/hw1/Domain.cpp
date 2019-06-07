
#include "Domain.h"


Domain::Domain(char v, int start, int end)
{
    this->variable = v;
    this->values = std::set<int>();

    for (int i = start; i <= end; i++)
    {
        values.insert(i);
    }
}

int Domain::getSize()
{
    return values.size();
}

bool Domain::operator<(const Domain &other)
{
    return (this->values.size() < other.values.size());
}

void Domain::updateDomain(std::list<int> &newVals)
{
    values.clear();
    for (int newVal : newVals)
    {
        values.insert(newVal);
    }
}

std::set<int> Domain::getDomain()
{
    return values;
}

char Domain::getVar()
{
    return variable;
}

Domain::Domain(const Domain &otherDomain)
{
    this->variable=otherDomain.variable;
    this->values=otherDomain.values;
}

Domain &Domain::operator=(const Domain& otherDomain)
{
    if(this != &otherDomain)
    {
        this->variable=otherDomain.variable;
        this->values=otherDomain.values;
    }
    return *this;
}

Domain::Domain(Domain *pDomain)
{
    this->variable=pDomain->variable;
    this->values=pDomain->values;
}

