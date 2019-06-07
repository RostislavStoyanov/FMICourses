
#ifndef HW1_ASSIGNMENT_H
#define HW1_ASSIGNMENT_H
#include<unordered_map>
#include <stdio.h>

class Assignment
{
private:
    std::unordered_map<char,int> assignments;
public:
    Assignment();

    int getAssignment(char var) const;

    void addAssignment(char var, int value);

    void printToConsole() const;

    void printCurr();
};


#endif //HW1_ASSIGNMENT_H
