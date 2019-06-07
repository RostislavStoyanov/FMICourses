#ifndef HW2_ITEM_H
#define HW2_ITEM_H


#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static const char DEILIMITER  = ',';

class Item
{

private:
    long double attributes[4];
    int idx;
    int clusterId;

public:
    Item();

    long double getSepalLength() const;

    long double getSepalWidth() const;

    long double getPetalLength() const;

    long double getPetalWidth() const;

    int getClusterId() const;

    const long double *getAttributes() const;

    void setClusterId(int clusterId);

    void readNextItem(std::istream& istream);

    friend std::istream & operator >> (std::istream &istream,  Item &item);

    long double euclideanDistance(const std::vector<long double>& centroid);

    long double manhattanDistance(const std::vector<long double>& centroid);

    long double minkowski3(const std::vector<long double>& centroid);

    bool operator< (const Item& item);
};


#endif //HW2_ITEM_H
