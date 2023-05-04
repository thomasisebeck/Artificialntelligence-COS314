#pragma once
#include <vector>
#include "sharedTypes.h"

class Knapsack {
private:
    std::vector<Item> items;
    int totalWeight;
public:
    Knapsack(std::vector<Item> items, int totalWeight);
};

