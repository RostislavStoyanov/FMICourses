#include <iostream>
#include "State.h"

bool backtrack(State *currState)
{

    if (!currState->canContinue())
    {
        return currState->isFinal();
    }

    char var = currState->getSmallestDomainVar();
    bool ans = false;

    auto domain = new Domain(currState->getDomainForVar(var));

    for (int val : domain->getDomain())
    {
        if (var >= 'A' && var <= 'I' && !currState->canUseValue(val))
            continue;
        State *nextState = new State(currState);
        nextState->updateVar(var, val);
        if (nextState->isConsistentWithConstraints())
        {
            if (backtrack(nextState))
                ans = true;
        }
        delete nextState;
    }

    delete domain;

    return ans;
}


int main()
{
    State *initialState = new State();
    initialState->updateVar('B', 1);
    initialState->updateVar('Z', 1);

    bool ans = backtrack(initialState);
    if (!ans)
    {
        std::cout << "No solutions found" << std::endl;
    }

    delete initialState;

    return 0;
}