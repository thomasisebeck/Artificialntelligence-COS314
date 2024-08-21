#pragma once
#include <vector>
#include "sharedTypes.h"

class Knapsack {
private:
    int totalWeight;
    int populationSize;
protected:
    std::vector<Item> items;
public:
    Knapsack(std::vector<Item> items, int totalWeight, int populationSize);
    int getWeight() const;
    int getPopulationSize() const;
};

