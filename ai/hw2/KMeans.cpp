
#include "KMeans.h"

bool equalsDouble(long double d1, long double d2)
{
    return fabsl(d1 - d2) < 0.000001;
}

KMeans::KMeans(std::vector<Item> &items)
{
    this->items = items;
    centroids = std::vector<std::vector<long double>>();
    oldCentroids = std::vector<std::vector<long double>>();
    for (int i = 0; i < 3; i++)
    {
        oldCentroids.emplace_back(std::vector<long double>(4));
    }
    SSE = 0;
    oldSSE = 0;

    initializeCentroids();
}


void KMeans::initializeCentroids()
{
    srand(time(nullptr));

    int i = 0;
    while (i < 3)
    {

        int randomIdx = (rand() % items.size());
        if (items[randomIdx].getClusterId() != -1)
            continue;
        items[randomIdx].setClusterId(i++);
        centroids.emplace_back(items[randomIdx].getAttributes(), items[randomIdx].getAttributes() + 4);
        initialCentroids.emplace_back(items[randomIdx].getAttributes(), items[randomIdx].getAttributes() + 4);
    }
}

void KMeans::assignClusters(int distType)
{
    SSE = 0;
    std::vector<long double> distances(3);
    for (Item &i : items)
    {
        if (distType == 1)
        {
            for (int j = 0; j < 3; j++)
                distances[j] = i.euclideanDistance(centroids[j]);
        }
        else if (distType == 2)
        {
            for (int j = 0; j < 3; j++)
                distances[j] = i.manhattanDistance(centroids[j]);
        }
        else
        {
            for (int j = 0; j < 3; j++)
                distances[j] = i.minkowski3(centroids[j]);
        }
        int idxMin = std::distance(distances.begin(), std::min_element(distances.begin(), distances.end()));
        i.setClusterId(idxMin);


        long double dist = 0;
        if (distType == 1)
        {
            dist = i.euclideanDistance(centroids[idxMin]);
        }
        else if (distType == 2)
        {
            dist = i.manhattanDistance(centroids[idxMin]);
        }
        else
        {
            dist = i.minkowski3(centroids[idxMin]);
        }

        SSE += (dist * dist);
    }
}

void KMeans::calculateNewCentroids()
{
    int idx;
    int clusterSize[3]{0, 0, 0};
    long double values[3][4]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (Item i : items)
    {
        idx = i.getClusterId();
        values[idx][0] += i.getSepalLength();
        values[idx][1] += i.getSepalWidth();
        values[idx][2] += i.getPetalLength();
        values[idx][3] += i.getPetalWidth();
        clusterSize[idx]++;
    }


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            values[i][j] = values[i][j] / clusterSize[i];
            oldCentroids[i][j] = centroids[i][j];
            centroids[i][j] = values[i][j];
        }
    }
}

void KMeans::runAlgorithm(int distType)
{
    while (true)
    {
        assignClusters(distType);
        calculateNewCentroids();
        if (criteria2())
            break;
        else
            oldSSE = SSE;
    }

    printOutput();
}

bool KMeans::endCriteriaReached()
{
    return equalsDouble(oldSSE, SSE);
}

void KMeans::printOutput()
{
    std::sort(items.begin(), items.end());

    long double totalDifferent = getDifferent(0, 49, 1) + getDifferent(50, 99, 2) + getDifferent(100, 149, 3);
    long double accuraccy = 1 - (totalDifferent / items.size());
    std::cout << "Total accuraccy: " << accuraccy << std::endl << std::endl;
}

int KMeans::getDifferent(int startIdx, int endIdx, int idx)
{
    int clustersCount[3]{0, 0, 0};
    int diff = 0;
    for (int i = startIdx; i <= endIdx; i++)
    {
        clustersCount[items[i].getClusterId()]++;
    }
    int maxIdx = std::distance(clustersCount, std::max_element(clustersCount, clustersCount + 3));
    for (int i = 0; i < 3; i++)
    {
        if (i != maxIdx)
            diff += clustersCount[i];
    }
    std::cout << "Cluster " << idx << " difference count - " << diff << std::endl;
    return diff;
}

bool KMeans::criteria2()
{
    bool stop = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!equalsDouble(oldCentroids[i][j], centroids[i][j]))
                stop = false;
        }
    }
    return stop;
}

KMeans::KMeans(std::vector<Item> &items, const std::vector<std::vector<long double>> &centroids)
{
    this->items = items;
    this->centroids = centroids;
    oldCentroids = std::vector<std::vector<long double>>();
    for (int i = 0; i < 3; i++)
    {
        oldCentroids.emplace_back(std::vector<long double>(4));
    }
    SSE = 0;
    oldSSE = 0;
    initialCentroids = centroids;
}

const std::vector<std::vector<long double>> &KMeans::getCentroids() const
{
    return initialCentroids;
}

