#pragma once
#include "sharedTypes.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class ACO {
    //2d array of items to connect
    std::vector<Item> items;
    std::vector<int> indices;
    float totalWeight;
    float pheromonesToDeposit;
    float evaporationRate;
    float bestValue;
    string bestSolution;
    int getNextItem(vector<int> visitedItems);
public:
    ACO(std::vector<Item> items, float totalWeight, float pheremonesToDeposit, float evaporationRate);
    float getValue();
    string getBestSolution();
    void travelRoute();
    float getBestFitness();
};
