#include "Network.h"
#include <iostream>
using namespace std;

Network::Network(std::vector<int> topology, double alpha) {
    this->topo = topology;
    this->weightMatrices = {};
    this->valuesMatrices = {};
    this->biasMatrices = {};
    this->alpha = alpha;

    //build with topology
    for (int i = 0; i < topology.size() - 1; i++) {
        Matrix weights(topology[i + 1], topology[i]);
        weights = weights.operation(RANDOM);
        weightMatrices.push_back(weights);

        Matrix bias(topology[i + 1], 1);
        bias = bias.operation(RANDOM);
        biasMatrices.push_back(bias);
    }
    valuesMatrices.resize(topology.size());

    for (int i = 0; i < valuesMatrices.size(); i++)
        for (int r = 0; r < valuesMatrices[i].rows; r++)
            for (int c = 0; c < valuesMatrices[i].cols; c++)
                valuesMatrices[i].get(c, r) = 0;

}

void Network::printWeights() {
    for (Matrix m : weightMatrices)
        m.print();
}

void Network::feedForward(std::vector<double> input) {
    if (input.size() != topo[0])
        throw "Input size is not equal to topology";

    //convert input to a matrix of a sigle row
    Matrix currValues(input.size(), 1);

    //copy the values to the matrix
    for (int i = 0; i < input.size(); i++)
        currValues.values[i] = input[i];

    //do the feedforward
    for (int i = 0; i < weightMatrices.size(); i++){
        //connections will be n - 1 layers
        //weights is 1 less than topo

        valuesMatrices[i] = currValues;

        //multiply by the weights
        currValues = currValues.mult(weightMatrices[i]);

        //add the bias for the row
        currValues = currValues.add(biasMatrices[i]);

        //activate the neurons
        currValues = currValues.operation(SIGMOID);
    }

    valuesMatrices[valuesMatrices.size() - 1] = currValues;

}

void Network::printNodes() {
    for (int i = 0; i < valuesMatrices.size(); i++) {
        cout << "layer " << i << ": " << valuesMatrices[i].cols << " by  " << valuesMatrices[i].rows << endl;
        valuesMatrices[i].print();
    }
}

