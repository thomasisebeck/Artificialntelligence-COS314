#include "Knapsack.h"
#include <vector>
using namespace std;

Knapsack::Knapsack(vector<Item> items, int totalWeight, int populationSize) {
    this->items = items;
    this->totalWeight = totalWeight;
    this->populationSize = populationSize;
}

int Knapsack::getWeight() const {
    return this->totalWeight;
}

int Knapsack::getPopulationSize() const {
    return this->populationSize;
}