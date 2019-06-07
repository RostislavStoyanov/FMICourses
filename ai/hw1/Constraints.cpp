#include <iostream>
#include "Constraints.h"


bool Constraints::endCheck(Assignment const &assignment)
{
    //construct numbers
    int numberABC = 0, numberDEB = 0, numberEDBDFC = 0;
    int currDigit;

    currDigit = assignment.getAssignment('A');
    numberABC += 100 * currDigit;

    currDigit = assignment.getAssignment('B');
    numberABC += 10 * currDigit;
    numberDEB += currDigit;
    numberEDBDFC += 1000 * currDigit;

    currDigit = assignment.getAssignment('C');
    numberABC += currDigit;
    numberEDBDFC += currDigit;

    currDigit = assignment.getAssignment('D');
    numberDEB += 100 * currDigit;
    numberEDBDFC += 10000 * currDigit;
    numberEDBDFC += 100 * currDigit;

    currDigit = assignment.getAssignment('E');
    numberDEB += 10 * currDigit;
    numberEDBDFC += 100000 * currDigit;

    currDigit = assignment.getAssignment('F');
    numberEDBDFC += 10 * currDigit;

    //check if multiplicgetAssignmention is correct
    if (numberABC * numberDEB == numberEDBDFC)
    {
        assignment.printToConsole();
        return true;
    }
    return false;
}

bool Constraints::isConsistent(const Assignment &assignments, const std::vector<bool> &letters,
                               const std::vector<bool> &others)
{
    //EC == G + 10T
    if (letters['E' - 'A'] && letters['C' - 'A'] && letters['G' - 'A'] && others['T' - 'T'])
    {
        if (assignments.getAssignment('E') * assignments.getAssignment('C') !=
            assignments.getAssignment('G') + 10 * assignments.getAssignment('T'))
            return false;
    }

    //T + E == A + 10 U
    if (letters['E' - 'A'] && letters['A' - 'A'] && others['U' - 'T'] && others['T' - 'T'])
    {
        if (assignments.getAssignment('E') + assignments.getAssignment('T') !=
            assignments.getAssignment('A') + 10 * assignments.getAssignment('U'))
            return false;
    }

    //U+ EA = I
    if (letters['E' - 'A'] && letters['A' - 'A'] && others['U' - 'T'] && letters['I' - 'A'])
    {
        if ((assignments.getAssignment('E') * assignments.getAssignment('A')) + assignments.getAssignment('U') !=
            assignments.getAssignment('I'))
            return false;
    }

    //DC = A + 10 V
    if (letters['D' - 'A'] && letters['C' - 'A'] && letters['A' - 'A'] && others['V' - 'T'])
    {
        if ((assignments.getAssignment('C') * assignments.getAssignment('D')) !=
            assignments.getAssignment('A') + 10 * assignments.getAssignment('V'))
            return false;
    }

    //D + V = F + 10 W
    if (letters['D' - 'A'] && letters['F' - 'A'] && others['V' - 'T'] && others['W' - 'T'])
    {
        if (assignments.getAssignment('D') + assignments.getAssignment('V') !=
            assignments.getAssignment('F') + 10 * assignments.getAssignment('W'))
            return false;
    }

    //W + AD = H + 10 E
    if (letters['D' - 'A'] && letters['A' - 'A'] && letters['H' - 'A'] && letters['E' - 'A'] && others['W' - 'T'])
    {
        if ((assignments.getAssignment('A') * assignments.getAssignment('D')) + assignments.getAssignment('W') !=
            assignments.getAssignment('H') + 10 * assignments.getAssignment('E'))
            return false;
    }

    //B + G == F + 10 * X
    if (letters['B' - 'A'] && letters['G' - 'A'] && letters['F' - 'A'] && others['X' - 'T'])
    {
        if (assignments.getAssignment('B') + assignments.getAssignment('G') !=
            assignments.getAssignment('F') + 10 * assignments.getAssignment('X'))
            return false;
    }

    //X + 3 * A == D + 10 * Y
    if (letters['A' - 'A'] && letters['D' - 'A'] && others['X' - 'X'] && others['Y' - 'T'])
    {
        if (assignments.getAssignment('X') + 3 * assignments.getAssignment('A') !=
            assignments.getAssignment('D') + 10 * assignments.getAssignment('Y'))
            return false;
    }


    //Y + I + F == B + 10 * Z
    if (letters['B' - 'A'] && letters['I' - 'A'] && letters['F' - 'A'] && others['Y' - 'T'] && others['Z' - 'T'])
    {
        if (assignments.getAssignment('Y') + assignments.getAssignment('I') + assignments.getAssignment('F') !=
            assignments.getAssignment('B') + 10 * assignments.getAssignment('Z'))
            return false;
    }

    //Z + H = D
    if (letters['H' - 'A'] && letters['D' - 'A'] && others['Z' - 'T'])
    {
        if (assignments.getAssignment('Z') + assignments.getAssignment('H') != assignments.getAssignment('D'))
            return false;
    }


    //ABC required for all the other constraints
    if (letters['A' - 'A'] && letters['B' - 'A'] && letters['C' - 'A'])
    {
        //construct ABC
        int numberABC = 100 * assignments.getAssignment('A') + 10 * assignments.getAssignment('B') +
                        assignments.getAssignment('C');

        //B * ABC == ABC
        if (assignments.getAssignment('B') * numberABC != numberABC)
            return false;

        //E * ABC == IAG
        if (letters['E' - 'A'] && letters['I' - 'A'] && letters['G' - 'A'])
        {
            //construct IAG
            int numberIAG = 100 * assignments.getAssignment('I') + 10 * assignments.getAssignment('A') +
                            assignments.getAssignment('G');

            if (assignments.getAssignment('E') * numberABC != numberIAG)
                return false;
        }

        //D * ABC = EHFA
        if (letters['E' - 'A'] && letters['D' - 'A'] && letters['H' - 'A'] && letters['F' - 'A'])
        {
            //construct EHFA
            int numberEHFA =
                    1000 * assignments.getAssignment('E') + 100 * assignments.getAssignment('H') +
                    10 * assignments.getAssignment('F') + assignments.getAssignment('A');
            if (assignments.getAssignment('D') * numberABC != numberEHFA)
                return false;
        }
    }

    return true;
}

void helper(double mult1, double mult2, int sign, char otherLetter, char ansLetter, std::vector<bool> &letters,
            std::vector<bool> &others, std::unordered_map<char, Domain *> &domains, Assignment &prevAssignments)
{
    std::list<int> updateList;

    if (others[otherLetter - 'T'])
    {
        int other = prevAssignments.getAssignment(otherLetter);
        updateList.push_back(mult1 * mult2 + other);
        domains.at(ansLetter)->updateDomain(updateList);
    }
    else
    {
        auto domain = domains.at(otherLetter)->getDomain();
        for (int val : domain)
        {
            double value = (mult1 * mult2 + (sign * (val / mult2)));
            double intpart;
            if ((modf(value, &intpart) == 0.0))
                updateList.push_back(value);
        }

        domains.at(ansLetter)->updateDomain(updateList);
    }
}

void helper2(double coef, int add1, int add2, char otherLetter, char ansLetter, std::vector<bool> &letters,
             std::vector<bool> &others,
             std::unordered_map<char, Domain *> &domains, Assignment &prevAssignments)
{
    std::list<int> updateList;
    if (others[otherLetter - 'T'])
    {
        int other = prevAssignments.getAssignment(otherLetter);
        updateList.push_back(add1 + add2 + (coef * other));
        domains.at(ansLetter)->updateDomain(updateList);
    }
    else
    {
        auto domain = domains.at(otherLetter)->getDomain();

        for (int val : domain)
        {
            double value = add1 + add2 + (coef * val);
            double intpart;
            if ((modf(value, &intpart) == 0.0))
                updateList.push_back(value);
        }

        domains.at(ansLetter)->updateDomain(updateList);
    }
}

void helper3(double coefExtra1, double coefExtra2, double coefVar, int var1, char extra1, char extra2, char goal,
             std::vector<bool> &letters, std::vector<bool> &others,
             std::unordered_map<char, Domain *> &domains, Assignment &prevAssignments)
{
    std::list<int> updateList;

    auto dom1 = domains.at(extra1)->getDomain();
    auto dom2 = domains.at(extra2)->getDomain();

    for (int val1 : dom1)
    {
        for (int val2:dom2)
        {
            double value = (coefVar * var1) + (coefExtra1 * val1) + (coefExtra2 * val2);
            double intpart;
            if ((modf(value, &intpart) == 0.0))
                updateList.push_back(value);
        }
    }

    domains.at(goal)->updateDomain(updateList);
}

void Constraints::updateDomainsOnAssignment(std::unordered_map<char, Domain *> &domains, char var, int val,
                                            Assignment &prevAssignments,
                                            std::vector<bool> &letters, std::vector<bool> &others)
{
    //H + Z == D Z == 1
    if (var == 'H' || var == 'D')
    {
        std::list<int> answerList(1);
        if (letters['H' - 'A'] && !letters['D' - 'A'])
        {
            answerList.push_back(1 + prevAssignments.getAssignment('H'));
            domains.at('D')->updateDomain(answerList);
            return;
        }
        else if (!letters['H' - 'A'] && letters['D' - 'A'])
        {
            answerList.push_back(prevAssignments.getAssignment('D') - 1);
            domains.at('H')->updateDomain(answerList);
            return;
        }
    }


    //E*A + Y = I
    if (var == 'A' || var == 'E' || var == 'I')
    {
        //we have E and A but not I
        if (letters['E' - 'A'] && !letters['I' - 'A'] && letters['A' - 'A'])
        {
            //I = EA + Y = EA + A(Y/A)
            helper(prevAssignments.getAssignment('E'), prevAssignments.getAssignment('A'),
                   prevAssignments.getAssignment('A'), 'Y', 'I', letters, others, domains, prevAssignments);
        }
            //we have E and I but not A
        else if (letters['I' - 'A'] && letters['E' - 'A'] && !letters['A' - 'A'])
        {
            //A = I/E - Y/E
            helper(prevAssignments.getAssignment('I'), (1 / prevAssignments.getAssignment('E')), -1, 'Y', 'A', letters,
                   others, domains, prevAssignments);
        }

            //we have I and A but not E
        else if (letters['I' - 'A'] && !letters['E' - 'A'] && letters['A' - 'A'])
        {
            //E = (I / A) - (Y / A)
            helper(prevAssignments.getAssignment('I'), (1 / prevAssignments.getAssignment('A')), -1, 'Y', 'E', letters,
                   others, domains, prevAssignments);
        }
    }

    //B+G = F + 10 * X
    if (var == 'B' || var == 'G' || var == 'F')
    {
        //have B and G not F
        if (letters['B' - 'A'] && letters['G' - 'A'] && !letters['F' - 'A'])
        {
            // F = B + G - 10 * X
            helper2(-10, prevAssignments.getAssignment('B'), prevAssignments.getAssignment('G'), 'X', 'F', letters,
                    others, domains, prevAssignments);
        }

            //have B and F but not G
        else if (letters['B' - 'A'] && !letters['G' - 'A'] && letters['F' - 'A'])
        {
            //G = F +10X - B
            helper2(10, prevAssignments.getAssignment('F'), -(prevAssignments.getAssignment('B')), 'X', 'G', letters,
                    others, domains, prevAssignments);
        }

            //have G and F but not B
        else if (!letters['B' - 'A'] && letters['G' - 'A'] && letters['F' - 'A'])
        {
            //B = F + 10X - G
            helper2(10, prevAssignments.getAssignment('F'), -(prevAssignments.getAssignment('G')), 'X', 'F', letters,
                    others, domains, prevAssignments);
        }
    }

    //EC = G + 10 * T
    if (var == 'B' || var == 'C' || var == 'G')
    {
        //have E and C not G
        if (letters['E' - 'A'] && letters['C' - 'A'] && !letters['G' - 'A'])
        {
            //G = EC - 10 T
            helper2(-10, 0, (prevAssignments.getAssignment('C') * prevAssignments.getAssignment('E')), 'T', 'G',
                    letters, others, domains, prevAssignments);
        }
            //have E and G not C
        else if (letters['E' - 'A'] && letters['C' - 'A'] && !letters['G' - 'A'])
        {
            //C = G/E + (10/E)T
            int div = prevAssignments.getAssignment('E');
            helper2((10 / div), 0, (prevAssignments.getAssignment('G') / div), 'T', 'C', letters, others, domains,
                    prevAssignments);
        }

            //have G and C not E
        else if (letters['E' - 'A'] && letters['C' - 'A'] && !letters['G' - 'A'])
        {
            //E = G/C + (10/C)T
            int div = prevAssignments.getAssignment('C');
            helper2((10 / div), 0, (prevAssignments.getAssignment('G') / div), 'T', 'E', letters, others, domains,
                    prevAssignments);
        }
    }

    //DC = A + 10 * V
    if (var == 'D' || var == 'C' || var == 'A')
    {
        // have D and C not A
        if (letters['D' - 'A'] && letters['C' - 'A'] && !letters['A' - 'A'])
        {
            helper2(-10, 0, (prevAssignments.getAssignment('D') * prevAssignments.getAssignment('C')), 'V', 'A',
                    letters, others, domains, prevAssignments);
        }
            // have D and A not C
        else if (letters['D' - 'A'] && !letters['C' - 'A'] && letters['A' - 'A'])
        {
            int div = prevAssignments.getAssignment('D');
            helper2((10 / div), 0, (prevAssignments.getAssignment('A') / div), 'V', 'C', letters, others, domains,
                    prevAssignments);
        }
            // have A and C not D
        else if (letters['D' - 'A'] && !letters['C' - 'A'] && letters['A' - 'A'])
        {
            int div = prevAssignments.getAssignment('C');
            helper2((10 / div), 0, (prevAssignments.getAssignment('A') / div), 'V', 'D', letters, others, domains,
                    prevAssignments);
        }
    }

    //T + E == A + 10 * U
    if (var == 'E' || var == 'A')
    {
        if (letters['E' - 'A'] && !letters['A' - 'A'])
            helper3(-10, 1, 1, prevAssignments.getAssignment('E'), 'U', 'T', 'A', letters, others, domains,
                    prevAssignments);
        else if (!letters['E' - 'A'] && letters['A' - 'A'])
            helper3(10, -1, 1, prevAssignments.getAssignment('A'), 'U', 'T', 'E', letters, others, domains,
                    prevAssignments);
    }

    //D + V == F + 10 * W
    if (var == 'D' || var == 'F')
    {
        if (letters['D' - 'A'] && !letters['F' - 'A'])
            helper3(-10, 1, 1, prevAssignments.getAssignment('D'), 'W', 'V', 'F', letters, others, domains,
                    prevAssignments);
        else if (!letters['D' - 'A'] && letters['F' - 'A'])
            helper3(10, -1, 1, prevAssignments.getAssignment('F'), 'W', 'V', 'D', letters, others, domains,
                    prevAssignments);
    }

    //X + 3A == D + 10Y
    if (var == 'A' || var == 'D')
    {
        if (letters['A' - 'A'] && !letters['D' - 'A'])
            helper3(-10, 1, 3, prevAssignments.getAssignment('A'), 'Y', 'X', 'D', letters, others, domains,
                    prevAssignments);
        else if (!letters['A' - 'A'] && letters['D' - 'A'])
            helper3((10 / 3), (-1 / 3), (1 / 3), prevAssignments.getAssignment('D'), 'Y', 'X', 'A', letters, others,
                    domains,
                    prevAssignments);
    }

    //Y + I + F == B  + 10*Z == 11

    if (var == 'I' || var == 'D')
    {
        std::list<int> answerList;
        if (letters['I' - 'A'] && !letters['F' - 'A'])
        {
            auto domain = domains.at('Y')->getDomain();

            for (int v :domain)
            {
                answerList.push_front(11 - prevAssignments.getAssignment('I') - v);
            }
            domains.at('F')->updateDomain(answerList);
        }

        else if (!letters['I' - 'A'] && letters['F' - 'A'])
        {
            auto domain = domains.at('Y')->getDomain();

            for (int v : domain)
            {
                answerList.push_back(11 - prevAssignments.getAssignment('F') - v);
            }
            domains.at('I')->updateDomain(answerList);
        }
    }

    //W + AD  = H + 10E
    if(var == 'A' || var =='D' || var == 'H' || var == 'E')
    {
        if(letters['A'-'A'] &&letters['D'-'A']&& others['W' - 'T'])
        {
            int ans = (prevAssignments.getAssignment('A') * prevAssignments.getAssignment('D')) + prevAssignments.getAssignment('W');
            std::list<int> answerList1;
            std::list<int> answerList2;
            answerList1.push_back(ans%10);
            answerList2.push_back(ans/10);

            domains.at('H')->updateDomain(answerList2);
            domains.at('E')->updateDomain(answerList1);
        }
    }
}

void Constraints::addTo(int idx, const std::list<char> &letters)
{
    int i;
    for (char c :letters)
    {
        if (c >= 'A' && c <= 'I')
            i = (int) (c - 'A');
        else
            i = int(c - 'T' + 9);

        graph[i].push_back(idx);
        graph[idx].push_back(i);
    }
}

Constraints::Constraints()
{
    graph = std::vector<std::vector<int>>(26);
    //     EC = G + 10T
    addTo(16, std::list<char>{'E', 'C', 'G', 'T'});
    //      T + E = A + 10U
    addTo(17, std::list<char>{'T', 'E', 'A', 'U'});
    //      U + EA = I
    addTo(18, std::list<char>{'U', 'E', 'A', 'I'});
    //      DC = A + 10V
    addTo(19, std::list<char>{'D', 'C', 'A', 'V'});
    //      D + V = F + 10 W
    addTo(20, std::list<char>{'D', 'V', 'F', 'W'});
    //      W + AD = H + 10 E
    addTo(21, std::list<char>{'W', 'A', 'D', 'H', 'E'});
    //      B+ G = F + 10 X
    addTo(22, std::list<char>{'B', 'G', 'F', 'X'});
    //      X +3A = F + 10 Y
    addTo(23, std::list<char>{'X', 'A', 'F', 'Y'});
    //      Y+ I + F = B + 10 Z
    addTo(24, std::list<char>{'Y', 'I', 'F', 'B', 'Z'});
    //      Z + H = D
    addTo(25, std::list<char>{'Z', 'H', 'D',});
}

char Constraints::getMostConstraining(const std::list<char> &letters)
{
    int idx;
    int max = 0;
    char currAnswer = 'L';

    for (char c :letters)
    {
        if (c >= 'A' && c <= 'I')
            idx = (int) (c - 'A');
        else
            idx = int(c - 'T' + 9);

        int count = 0;

        for (int i : graph[idx])
        {
            count += (graph[i].size() - 1);
        }
        if (count > max)
        {
            max = count;
            currAnswer = c;
        }

    }
    return currAnswer;
}


