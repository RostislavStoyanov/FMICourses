#ifndef HW2_KMEANS_H
#define HW2_KMEANS_H


#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <time.h>
#include "Item.h"


class KMeans
{
private:
    std::vector<Item> items;
    std::vector<std::vector<long double>> centroids;
    long double SSE;
    long double oldSSE;
    std::vector<std::vector<long double>> oldCentroids;
    std::vector<std::vector<long double>> initialCentroids;

    void initializeCentroids();

    int getDifferent(int, int, int);

public:
    explicit KMeans(std::vector<Item> &);

    KMeans(std::vector<Item> &,const std::vector<std::vector<long double>>&);

    void runAlgorithm(int);

    void assignClusters(int);

    void calculateNewCentroids();

    bool endCriteriaReached();

    void printOutput();

    bool criteria2();

    const std::vector<std::vector<long double>> &getCentroids() const;
};


#endif //HW2_KMEANS_H
