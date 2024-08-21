#pragma once
#include <cstdlib>
#include <vector>
#include <fstream>
#include "Matrix.h"

class Network {
private:
    std::vector<int> topo;
    std::vector<Matrix> weightMatrices;
    std::vector<Matrix> valuesMatrices;
    std::vector<Matrix> biasMatrices;
    double alpha;
public:
    Network(std::vector<int> topology, double alpha, unsigned int SEED);
    void printWeights();
    void printNodes();
    void feedForward(std::vector<double> input);
    bool backProp(std::vector<double> targetOutput);
    std::vector<double> getOutputValues();
    void storeWeights();
    void loadWeights();
};


