#include <utility>
#include <list>
#include <iostream>
#include "Genetic.h"

Genetic::Genetic(std::vector<Item> items, int totalWeight, int populationSize, float crossoverDecimal, float mutationRate, int tournamentSize)
            : Knapsack(items, totalWeight, populationSize) {

    //create set of 10 bitstrings....
    for (int j = 0; j < populationSize; j++) {

        //initialise the offspring list randomly
        vector<bool> bistring = {};

        for (int i = 0; i < items.size(); i++)
            //random true/false values at the start
            bistring.push_back(rand() % 2 == 0);

        offspring.push_back(bistring);
    }

    this->numCrossover = populationSize * crossoverDecimal;
    if (this->numCrossover % 2 != 0) //not an even number, change
        this->numCrossover--;

    //create the indices for crossover (pairs in the offspring array to crossover)
    for (int i = 0; i < offspring.size(); i++)
        crossoverIndices.push_back(i);

    this->tournamentSize = tournamentSize;

    this->mutationRate = mutationRate;
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

int Genetic::getBestFitnessIndex(vector< vector<bool> > individuals) {
    int bestFitness = getFitness(individuals[0]);
    vector< vector<bool> >::iterator iter;
    int index = 0;
    int bestIndex = 0;

    for (iter = individuals.begin(); iter != individuals.end(); iter++) {
        if (getFitness(*iter) > bestFitness) {
            bestFitness = getFitness(*iter);
            bestIndex = index;
        }
        index++;
    }

    return bestIndex;
}

vector<bool> Genetic::getBestIndividual(vector< vector<bool> > individuals) {
    int bestFitness = getFitness(individuals[0]);
    int bestIndex = 0;

    for (int i = 1; i < individuals.size(); i++) {
        if (getFitness(individuals[i]) > bestFitness) {
            bestFitness = getFitness(individuals[i]);
            bestIndex = i;
        }
    }

    return individuals[bestIndex];
}

std::vector<bool> Genetic::getBest() {
    return getBestIndividual(this->offspring);
}


void Genetic::tournamentSelection() {
    //select k individuals at random from the population
    //select the best on from those k individuals
    //repeat until reached desired population size

    vector< vector<bool> > tournament;
    vector< vector<bool> > newIndividuals;
    vector< vector<bool> > offspringCopy;
    vector<int> indicesToReplace;


    for (int i = 0; i < offspring.size(); i++) {

        offspringCopy.clear();
        vector< vector<bool> >::iterator iter;
        for (iter = offspring.begin(); iter != offspring.end(); iter++)
            offspringCopy.push_back(*iter);

        //create the tournament with k random individuals
        //while removing them from the current offspring
        for (int i = 0; i < tournamentSize; i++) {
            int randomNumber = rand() % offspringCopy.size();
            tournament.push_back(*offspringCopy.erase(offspringCopy.begin() + randomNumber));
        }

        //get the best individual in the tournament
        vector<bool> individual = getBestIndividual(tournament);

        //add this best individual to the new individuals
        newIndividuals.push_back(individual);

    }

    offspring = newIndividuals;

}

void Genetic::mutate() {
    //go through each bistring and mutate
    //check if we must mutate...

    for (int i = 0; i < offspring.size(); i++)
        if (rand() % 100 <= 100 * mutationRate) { //0 to 99, random number greater than mutation rate
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

    //copy the crossoverIndices array
    vector<int> indices;
    indices.clear();
    vector<int>::iterator iter;
    for (iter = crossoverIndices.begin(); iter != crossoverIndices.end(); iter++)
        indices.push_back(*iter);

    vector<int> chosenIndices;

    srand(time(NULL));

    //get random crossover indices to perform the crossover in pairs
    while (!indices.empty()) {

        int random;

        if (indices.size() == 1)
            random = 0;
        else
            random = rand() % indices.size();


        //add that value to the chose indices array
        int index = indices[random];
        chosenIndices.push_back(index);

        //remove the value from the index array
        auto value = indices.begin() + random;
        indices.erase(value);
    }

    //crossover the indices
    //get 2 at a time
    while (!chosenIndices.empty()) {
        int ind1 = chosenIndices.back();
        chosenIndices.pop_back();

        if (chosenIndices.empty())
            cout << "Is empty! something went wrong!" << endl;
        int ind2 = chosenIndices.back();
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