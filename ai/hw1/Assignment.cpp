#include <iostream>
#include "Assignment.h"

Assignment::Assignment()
{
    assignments = std::unordered_map<char, int>();
}

int Assignment::getAssignment(const char var) const
{
    return this->assignments.at(var);
}

void Assignment::addAssignment(char var, int value)
{
    assignments.insert(std::make_pair(var, value));
}

void Assignment::printToConsole() const
{
    printf("A = %d, B = %d, C = %d, D = %d,E = %d,F = %d,G = %d,H = %d,I = %d;T = %d, U = %d, V = %d, W = %d, X = %d, Y = %d, Z = %d \n", assignments.at('A'),
           assignments.at('B'), assignments.at('C'), assignments.at('D'), assignments.at('E'),
           assignments.at('F'), assignments.at('G'),
           assignments.at('H'), assignments.at('I'),
           assignments.at('T'),assignments.at('U'),
           assignments.at('V'),assignments.at('W'),
           assignments.at('X'),assignments.at('Y'),assignments.at('Z'));
}

void Assignment::printCurr()
{
    auto it = assignments.begin();
    auto end = assignments.end();

    while(it!=end)
    {
        std::cout<<(*it).first<<" - "<<(*it).second << ", ";
        it ++;
    }
    std::cout<<std::endl;
}
