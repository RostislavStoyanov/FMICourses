#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Item.h"
#include "KMeans.h"

int main()
{

    std::string pathToFile;
    std::cout << "Set the path to file:" << std::endl;
    std::cin >> pathToFile;

    std::ifstream file(pathToFile);
    if (!file)
    {
        std::cout << "Error when opening file" << std::endl;
        return 0;
    }

    std::vector<Item> items;
    Item rowItem;

    //drop the header line
    std::string temp;
    std::getline(file, temp);

    while (file >> rowItem)
    {
        items.push_back(rowItem);
    }

    std::cout<<"Starting the algorithm using euclidean distance:\n"<<"##########"<<std::endl;
    KMeans algo = KMeans(items);
    algo.runAlgorithm(1);

    std::cout<<"Starting the algorithm using manhattan distance:\n"<<"##########"<<std::endl;
    KMeans algo2 = KMeans(items,algo.getCentroids());
    algo2.runAlgorithm(2);

    std::cout<<"Starting the algorithm using minkowski distance with p = 4:\n"<<"##########"<<std::endl;
    KMeans algo3 = KMeans(items,algo.getCentroids());
    algo3.runAlgorithm(3);

    return 0;
}