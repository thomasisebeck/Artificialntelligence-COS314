#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "sharedTypes.h"
#include "Genetic.h"
#include "ACO.h"

using namespace std;

//ACO
int NUMBER_OF_ANT_TRAILS = 91;
float PHEROMONES_TO_DEPOSIT = 0.4;
int NUMBER_OF_RUNS_ACO = 60;
float EVAPORATION_RATE = 0.93;

//GA
const int POPULATION_SIZE = 50;
const float CROSSOVER_RATE = 0.8;
const float MUTATION_RATE = 0.4;
const int TOURNAMENT_SIZE = 8;
const int NUMBER_OF_GENERATIONS = 15;
const int NUMBER_OF_RUNS_GENETIC = 10;

float testInstance(problemInstance instance, testType type) {


    vector<bool> bestIndividual = {};

    switch (type) {
        case GENETIC:

            try {

                cout << "Genetic: " << instance.name << endl;

                //------------ timer
                auto start = std::chrono::steady_clock::now();
                //--------------

                for (int i = 0; i < NUMBER_OF_RUNS_GENETIC; i++) {

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

                    if (i == NUMBER_OF_RUNS_GENETIC - 1) {

                        //--------------------
                        auto end = std::chrono::steady_clock::now();
                        auto diff = end - start;
                        auto time = static_cast<double>(std::chrono::duration<double, std::milli> (diff).count())/1000;
                        //----------------------

                        cout << "Best individual: ";
                        gen.printBistring(bestIndividual);
                        cout << "Best fitness: " << gen.getFitness(bestIndividual) << endl;
                        cout << "Optimum: " << instance.optimum << endl;
                        cout << "Runtime: " << time << endl;
                    }

                }

            }
            catch (const char* err) {
                cout << "ERROR: " << err << endl;
            }

            break;

        case ANT:

            try {

                float bestValue = 0;
                string bestSolution;

                cout << "ACO: " << instance.name << endl;

                //------------ timer
                auto start = std::chrono::steady_clock::now();
                //--------------

                for (int i = 0; i < NUMBER_OF_RUNS_ACO; i++) {

                    ACO aco(instance.items, instance.capacity, PHEROMONES_TO_DEPOSIT,
                            EVAPORATION_RATE);

                    for (int j = 0; j < NUMBER_OF_ANT_TRAILS; j++)
                        aco.travelRoute();

                    if (aco.getValue() > bestValue) {
                        bestSolution = aco.getBestSolution();
                        bestValue = aco.getBestFitness();
                    }
                }

                //--------------------
                auto end = std::chrono::steady_clock::now();
                auto diff = end - start;
                auto time = static_cast<double>(std::chrono::duration<double, std::milli> (diff).count()) / 1000;
                //----------------------

                cout << "Best individual: " << bestSolution << endl;
                cout << "Best fitness: " << bestValue << endl;
                cout << "Optimum: " << instance.optimum << endl;
                cout << "Runtime: " << time << endl;

                //return the current solution
                return bestValue;

            }
            catch (const char * err) {
                cout << "ERROR: " << err << endl;
            }
    }

    return 0;
}

struct fileType {
    string filename;
    double optimum;
};

int main() {

    vector<fileType> fileVector {
            { "Instances/f1_l-d_kp_10_269", 295}, //evap: 0.3
            { "Instances/f2_l-d_kp_20_878", 1024}, //evap: 0.3
            { "Instances/f3_l-d_kp_4_20", 35}, //evap: 0.3
            { "Instances/f4_l-d_kp_4_11", 23}, //tails: 11, evap: 0.3
            { "Instances/f5_l-d_kp_15_375", 481.0694}, //trails: 79, runs: 45, evap: 0.8
            { "Instances/f6_l-d_kp_10_60", 52}, //trails: 4, evap: 0.8
            { "Instances/f7_l-d_kp_7_50", 107}, //trials: 25, evap: 0.8
            { "Instances/knapPI_1_100_1000_1", 9147}, //phere: 0.41, trails: 91, runs: 49, evap: 0.86
            { "Instances/f8_l-d_kp_23_10000", 9767},
            { "Instances/f9_l-d_kp_5_80", 130},
            { "Instances/f10_l-d_kp_20_879", 1025}
    };

    vector<int> items;

    float bestPheremones = 0.4; //done
    int bestNumberOfTrails = 0;
    int bestNumberOfRuns = 0;
    float bestEvaporationRate = 0;
    float totalCurr = 0;
    float bestSolution = 0;


        //reset current
        totalCurr = 0;

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
                newItem.pheremoneLevel = 1;
                instance.items.push_back(newItem);
            }

            myFile.close();

            testInstance(instance, GENETIC);
            testInstance(instance, ANT);
        }
        //check if it's better than optimum

        //cout << "TOTALCURR " << totalCurr << endl;
        //cout << "BEST " << bestSolution << endl;


       /* if (totalCurr > bestSolution) {
            bestSolution = totalCurr;
            bestPheremones = PHEROMONES_TO_DEPOSIT;
            bestNumberOfTrails = NUMBER_OF_ANT_TRAILS;
            bestNumberOfRuns = NUMBER_OF_RUNS_ACO;
            bestEvaporationRate = EVAPORATION_RATE;
        }*/

        //EVAPORATION_RATE += 0.01;
        //PHEROMONES_TO_DEPOSIT += 0.01;
        //NUMBER_OF_ANT_TRAILS += 1;
        //NUMBER_OF_RUNS_ACO += 1;


//    cout << "Best pheremone level: " << bestPheremones << endl;
//    cout << "Best number of trails: " << bestNumberOfTrails << endl;
//    cout << "Best number of runs: " << bestNumberOfRuns << endl;
//    cout << "Best evaporation rate: " << bestEvaporationRate << endl;

    return 0;

}