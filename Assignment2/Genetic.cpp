#include <utility>
#include <list>

#include "Genetic.h"

Genetic::Genetic(std::vector<Item> items, int totalWeight, int populationSize, float crossoverDecimal)
            : Knapsack(items, totalWeight, populationSize) {
    //initialise the offspring list randomly
    vector<bool> bistring;

    for (int i = 0; i < items.size(); i++)
        //random true/false values at the start
        bistring.push_back(rand() % 2 == 0);

    this->numCrossover = items.size() * crossoverDecimal;
    if (this->numCrossover % 2 != 0) //not an even number, change
        this->numCrossover--;

    //create the indices for crossover
    for (int i = 0; i < numCrossover; i++)
        crossoverIndices.push_back(i);
}

int Genetic::getFitness(const std::vector<bool> bistring) {
    //sum up the items and
    int instanceWeight = 0;
    int instanceValue = 0;

    for (int i = 0; i < bistring.size(); i++)
        if (bistring[i]) {
            //add the corresponding item
            instanceValue += items[i].weight;
            instanceValue += items[i].value;
            if (instanceWeight > getWeight())
                return 0; //over the weight limit
        }

    return instanceValue;
}

void Genetic::crossOver() {
    //select a subset for crossover

    //copy the indices array
    vector<int> indices = this->crossoverIndices;
    vector<int> chosenIndices;

    for (int i = 0; i < items.size(); i++) {
        //remove a random value
        auto value = indices.begin() + rand() % indices.size();
        //add that value to the chose indices array
        chosenIndices.push_back(*indices.erase(value));
    }

    //crossover the indices
    //get 2 at a time
    while (chosenIndices.size() > 0) {
        int ind1 = *chosenIndices.erase(chosenIndices.begin());
        int ind2 = *chosenIndices.erase(chosenIndices.begin());

        //crossover the 2 children
        vector<bool> child1 = offspring[ind1];
        vector<bool> child2 = offspring[ind2];
    }

}