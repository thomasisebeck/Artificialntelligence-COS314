#include <utility>
#include <list>
#include <iostream>
#include "Genetic.h"

Genetic::Genetic(std::vector<Item> items, int totalWeight, int populationSize, float crossoverDecimal, float mutationRate, int tournamentSize)
            : Knapsack(items, totalWeight, populationSize) {

    //create set of 10 bitstrings....
    for (int j = 0; j < tournamentSize; j++) {

        //initialise the offspring list randomly
        vector<bool> bistring = {};

        for (int i = 0; i < items.size(); i++)
            //random true/false values at the start
            bistring.push_back(rand() % 2 == 0);

        offspring.push_back(bistring);
    }

    this->numCrossover = items.size() * crossoverDecimal;
    if (this->numCrossover % 2 != 0) //not an even number, change
        this->numCrossover--;

    //create the indices for crossover (pairs in the offspring array to crossover)
    for (int i = 0; i < offspring.size(); i++)
        crossoverIndices.push_back(i);

    this->tournamentSize = tournamentSize;
}

int Genetic::getFitness(const std::vector<bool> bistring) {
    //sum up the items and
    int instanceWeight = 0;
    int instanceValue = 0;

    for (int i = 0; i < bistring.size(); i++)
        if (bistring[i]) {
            //add the corresponding item
            instanceWeight += items[i].weight;
            instanceValue += items[i].value;
            if (instanceWeight > getWeight())
                return 0; //over the weight limit
        }

    return instanceValue;
}

void Genetic::printBistring(vector<bool> bistring) {
    vector<bool>::iterator iter;
    for (iter = bistring.begin(); iter != bistring.end(); iter++)
        cout << (*iter == true ? "1" : "0");

    cout << "(" << getFitness(bistring) << ")" << endl;
}

void printIntVector(vector<int> vect) {
    vector<int>::iterator iter;
    for (iter = vect.begin(); iter != vect.end(); iter++)
        cout << (*iter);
    cout << endl;
}

void Genetic::printPopulation() {
    cout << "-------- population ----------" << endl;

    vector< vector<bool> >::iterator iter;
    for (iter = offspring.begin(); iter != offspring.end(); iter++)
        printBistring(*iter);


    cout << "------------------------------" << endl;
}

void Genetic::selection() {
    //select the fittest individuals until it reaches the tournament size
    //using routlette wheel

    std::vector< std::vector<bool> > newOffspring;

    for (int i = 0; i < tournamentSize; i++) {
        int ind1 = rand() % offspring.size();
        int ind2 = rand() % offspring.size();
        while (ind2 == ind1)
            ind2 = rand() % offspring.size();

        offspring[ind1];
        offspring[ind2];

        if (getFitness(offspring[ind1]) >= getFitness(offspring[ind2]))
            //select ind1
            newOffspring.push_back(offspring[ind1]);
        else
            //select ind2
            newOffspring.push_back(offspring[ind2]);
    }

    //select the fittest individuals
    offspring = newOffspring;

}

void Genetic::mutate() {
    //go through each bistring and mutate
    //check if we must mutate...

    for (int i = 0; i < offspring.size(); i++)
        if (rand() % 100 > 100 * mutationRate) { //0 to 99, random number greater than mutation rate
            //mutate the current offspring by flipping the bit
            int ind = rand() % offspring[i].size();
            if (offspring[i][ind] == 0)
                offspring[i][ind] = 1;
            else
                offspring[i][ind] = 0;
        }
}

void Genetic::crossOver() {
    //select a subset for crossover

    //copy the indices array
    vector<int> indices = this->crossoverIndices;
    vector<int> chosenIndices;

    srand(time(NULL));

    //get random crossover indices to perform the crossover in pairs
    while(indices.size() > 0) {

        int random = rand() % indices.size();
        while (random == 0)
            random = rand();
        //random number
        int randNumber = random % indices.size();


        //add that value to the chose indices array
        int index = indices[randNumber];
        chosenIndices.push_back(index);

        //remove the value from the index array
        auto value = indices.begin() + randNumber;
        indices.erase(value);
    }

    //crossover the indices
    //get 2 at a time
    while (chosenIndices.size() > 0) {
        int ind1 = chosenIndices[chosenIndices.size() - 1];
        chosenIndices.pop_back();
        int ind2 = chosenIndices[chosenIndices.size() - 1];
        chosenIndices.pop_back();

        //crossover the 2 parents
        vector<bool> parent1 = offspring[ind1];
        vector<bool> parent2 = offspring[ind2];

        //get a random index in the bitstring
        int randInd = rand() % (parent1.size() - 1) + 1;

        //change the offspring to be a crossover of teh parents
        for (int i = randInd; i < parent1.size(); i++)
            offspring[ind2][i] = parent1[i];
        for (int i = randInd; i < parent2.size(); i++)
            offspring[ind1][i] = parent2[i];

    }

}