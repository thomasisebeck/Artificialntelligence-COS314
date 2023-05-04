#pragma once
#include <vector>
#include <list>
#include "Knapsack.h"

class Genetic: public Knapsack {
private:
    std::vector< std::vector<bool> > offspring;
    std::vector<int> crossoverIndices;
    int numCrossover;
public:
    Genetic(std::vector<Item> items, int totalWeight, int populationSize, float crossoverDecimal);
    int getFitness(const std::vector<bool> bistring);
    void crossOver();
};