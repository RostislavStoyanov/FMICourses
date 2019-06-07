
#ifndef HW1_STATE_H
#define HW1_STATE_H

#include "Constraints.h"
#include "Assignment.h"
#include "Domain.h"
#include<vector>

class State
{
private:
    Assignment assignment; // current variable assignment

    std::unordered_map<char, Domain *> domains; //represent domains for each variable

    std::vector<bool> lettersValue; // value at idx represents if letter = idx + 'A' has been assigned a number

    std::vector<bool> othersValue; // value at idx represents if added letters(T,..X,Y,Z) have been assigned letter = idx + 'T'

    std::set<int> freeVals;

    std::vector<std::vector<int>> graph;

public:
    State();

    ~State();

    State(const State* pState);

    void updateVar(char letter, int value);

    bool isFinal();

    char getSmallestDomainVar();

    Domain *getDomainForVar(char var);

    bool isConsistentWithConstraints();

    bool canUseValue(int val);

    char getFirstPossible();

    bool canContinue();

};


#endif //HW1_STATE_H
