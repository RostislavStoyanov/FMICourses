
#ifndef HW1_CONSTRAINTS_H
#define HW1_CONSTRAINTS_H


#include <vector>
#include "Assignment.h"
#include "Domain.h"
#include <unordered_map>
#include<cmath>

class Constraints
{
    std::vector<std::vector<int>> graph;

    void addTo(int idx, const std::list<char> &letters);

public:
    Constraints();

    static Constraints &getInstance()
    {
        static Constraints instance;

        return instance;
    }

    Constraints(Constraints const &) = delete;

    void operator=(Constraints const &) = delete;

    static bool endCheck(Assignment const &assignment);

    static bool
    isConsistent(const Assignment &assignment, const std::vector<bool> &letters, const std::vector<bool> &others);

    static void
    updateDomainsOnAssignment(std::unordered_map<char, Domain *> &domains, char var, int val,
                              Assignment &prevAssignments,
                              std::vector<bool> &letters, std::vector<bool> &others);

    char getMostConstraining(const std::list<char> &);
};


#endif //HW1_CONSTRAINTS_H
