#include "Knapsack.h"
#include <vector>
using namespace std;

Knapsack::Knapsack(vector<Item> items, int totalWeight) {
    this->items = items;
    this->totalWeight = totalWeight;
}