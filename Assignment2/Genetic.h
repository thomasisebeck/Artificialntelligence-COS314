#pragma once
#include <vector>
#include <list>
#include "Knapsack.h"
#include "RouletteWheel.h"

class Genetic: public Knapsack {
private:
    std::vector< std::vector<bool> > offspring;
    std::vector<int> crossoverIndices;
    int numCrossover;
    int tournamentSize;
    float mutationRate;
public:
    Genetic(std::vector<Item> items, int totalWeight, int populationSize, float crossoverDecimal, float mutationRate, int tournamentSize);
    int getFitness(const std::vector<bool> bistring);
    void crossOver();
    void printPopulation();
    void mutate();
    void selection();
    void printBistring(vector<bool> bistring);
};