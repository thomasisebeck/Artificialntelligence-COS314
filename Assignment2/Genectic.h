#pragma once
#include <vector>
#include "Knapsack.h"

class Genetic: public Knapsack {
private:
    std::vector<bool> bits;
    std::vector< std::vector<bool> > offspring;
public:
    Genetic(std::vector<Item> items, int totalWeight);
    int getFitness(const std::vector<int>& bistring);
};