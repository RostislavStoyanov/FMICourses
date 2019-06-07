#include <limits>
#include "State.h"


State::State()
{
    lettersValue = std::vector<bool>(9, false);
    othersValue = std::vector<bool>(7, false);
    assignment = Assignment();
    domains = std::unordered_map<char, Domain *>(16);
    graph = std::vector<std::vector<int>>() ;

    for (int i = 0; i < 9; i++)
    {
        char letter = (char) ('A' + i);
        domains.insert(std::make_pair(letter, new Domain(letter, 1, 9)));
    }

    for (int i = 0; i < 7; i++)
    {
        char letter = (char) ('T' + i);
        if (i <= 4)
        {
            domains.insert(std::make_pair(letter, new Domain(letter, 0, 8)));
        }
        else
            domains.insert(std::make_pair(letter, new Domain(letter, 0, 2)));
    }
    freeVals = std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9};
}


bool State::isFinal()
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (lettersValue[i])
            count++;
    }

    for (int i = 0; i < 7; i++)
    {
        if (othersValue[i])
            count++;
    }
    if (count == 16)
        return Constraints::endCheck(assignment);
    return false;
}

char State::getSmallestDomainVar()
{
    auto it = domains.begin();
    int size = std::numeric_limits<int>::max();
    char var = 'L';
    std::list<char> tie;
    while (it != domains.end())
    {
        int currSize = (*it).second->getSize();
        if (currSize < size && currSize > 1 && (*it).first>= 'A' && (*it).first<='I')
        {
            size = currSize;
            var = (*it).first;
            tie.clear();
        }
        if(currSize == size && (*it).first>= 'A' && (*it).first<='I')
        {
            tie.push_back((*it).second->getVar());
        }
        it++;
    }

    if(var == 'L')
        var = Constraints::getInstance().getMostConstraining(tie);

    if (var == 'L')
        return getFirstPossible();
    return var;
}

void State::updateVar(char letter, int value)
{
    int idx;
    if (letter >= 'A' && letter <= 'I')
    {
        idx = (int) (letter - 'A');
        lettersValue[idx] = true;
    }
    else
    {
        idx = (int) (letter - 'T');
        othersValue[idx] = true;
    }

    std::list<int> n{value};
    domains.at(letter)->updateDomain(n);
    assignment.addAssignment(letter, value);
    Constraints::updateDomainsOnAssignment(domains,letter,value,assignment,lettersValue,othersValue);
    freeVals.erase(value);
}

Domain *State::getDomainForVar(char var)
{
    return domains.at(var);
}

bool State::isConsistentWithConstraints()
{
    return Constraints::isConsistent(assignment, lettersValue, othersValue);
}

State::State(const State *pState)
{
    this->assignment = Assignment(pState->assignment);
    this->domains = std::unordered_map<char, Domain *>();
    auto it = pState->domains.begin();
    auto end = pState->domains.end();

    while (it != end)
    {
        auto *nDom = new Domain((*it).second);
        domains.insert(std::make_pair((*it).first, nDom));
        it++;
    }
    this->lettersValue = std::vector<bool>(pState->lettersValue);
    this->othersValue = std::vector<bool>(pState->othersValue);
    this->freeVals = std::set<int>(pState->freeVals);
}

bool State::canUseValue(int val)
{
    return freeVals.count(val);
}

char State::getFirstPossible()
{
    for (int i = 0; i < 9; i++)
    {
        if (!lettersValue[i])
            return ((char) (i + 'A'));
    }

    for (int i = 0; i < 7; i++)
    {
        if (!othersValue[i])
        {
            char ans = ((char) (i + 'T'));
            return ans;
        }
    }
}

State::~State()
{
    auto it = domains.begin();
    auto end = domains.end();

    while(it != end)
    {
        delete (*it).second;
        it++;
    }
}

bool State::canContinue()
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (lettersValue[i])
            count++;
    }

    for (int i = 0; i < 7; i++)
    {
        if (othersValue[i])
            count++;
    }
    return count < 16;
}