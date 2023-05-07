#include <iostream>
#include <fstream>
#include <vector>
#include "sharedTypes.h"
#include "Genetic.h"
#include "RouletteWheel.h"
using namespace std;

void testInstance(problemInstance instance, testType type) {

    const int POPULATION_SIZE = 50;

    //must be even
    const float CROSSOVER_RATE = 0.8;
    const float MUTATION_RATE = 0.4;
    const int TOURNAMENT_SIZE = 8;
    const int NUMBER_OF_GENERATIONS = 25;
    const int NUMBER_OF_RUNS = 10;
    vector<bool> bestIndividual = {};

    switch (type) {
        case GENETIC:

            cout << "Genetic: " << instance.name << endl;

            for (int i = 0; i < NUMBER_OF_RUNS; i++) {

                //create a genetic class
                Genetic gen(instance.items, instance.capacity, POPULATION_SIZE,
                            CROSSOVER_RATE, MUTATION_RATE, TOURNAMENT_SIZE);

                for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
                    gen.crossOver();
                    gen.tournamentSelection();
                    gen.mutate();
                    if (bestIndividual.empty() || gen.getFitness(bestIndividual) < gen.getFitness(gen.getBest()))
                        bestIndividual = gen.getBest();
                }

                if (i == NUMBER_OF_RUNS - 1) {
                    cout << "Best individual: ";
                    gen.printBistring(bestIndividual);
                    cout << "Best fitness: " << gen.getFitness(bestIndividual) << endl;
                    cout << "Optimum: " << instance.optimum << endl;
                }

            }

    }
}

struct fileType {
    string filename;
    double optimum;
};

int main() {

    vector<fileType> fileVector {
            { "Instances/f1_l-d_kp_10_269", 295},
            { "Instances/f2_l-d_kp_20_878", 1024},
            { "Instances/f3_l-d_kp_4_20", 35},
            { "Instances/f4_l-d_kp_4_11", 23},
            { "Instances/f5_l-d_kp_15_375", 481.0694},
            { "Instances/f6_l-d_kp_10_60", 52},
            { "Instances/f7_l-d_kp_7_50", 107},
            { "Instances/knapPI_1_100_1000_1", 9147},
            { "Instances/f8_l-d_kp_23_10000", 9767},
            { "Instances/f9_l-d_kp_5_80", 130},
            { "Instances/f10_l-d_kp_20_879", 1025},
    };

    vector<int> items;

    for (fileType file: fileVector) {
        //clear vector
        items.clear();

        ifstream myFile(file.filename);

        //init the name and optimum
        problemInstance instance;
        instance.name = file.filename;
        instance.optimum = file.optimum;

        string line;

        //get first line: <no lines> <capacity>
        getline(myFile, line);

        //get the capacity
        line.erase(0, line.find(' ') + 1);
        instance.capacity = stoi(line);


        //load the values into the vector
        while (getline(myFile, line)) {
            Item newItem;
            newItem.value = stoi(line.substr(0, line.find(' ')));
            line.erase(0, line.find(' ') + 1);
            newItem.weight = stoi(line);
            instance.items.push_back(newItem);
        }

        myFile.close();

        //test
        testInstance(instance, GENETIC);

    }


    return 0;

}