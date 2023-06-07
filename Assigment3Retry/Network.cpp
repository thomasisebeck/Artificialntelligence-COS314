#include "Network.h"
#include <iostream>
#include <iomanip>
#include <limits>

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

    valuesMatrices[weightMatrices.size()] = currValues;

}

void Network::printNodes() {
    for (int i = 0; i < valuesMatrices.size(); i++) {
        cout << "layer " << i << ": " << valuesMatrices[i].cols << " by  " << valuesMatrices[i].rows << endl;
        valuesMatrices[i].print();
    }
}

void Network::backProp(vector<double> targetOutput) {
    if (targetOutput.size() != this->topo.back())
        throw "Target output incorrect size";

    Matrix outputErrors(targetOutput.size(), 1);
    outputErrors.values = targetOutput;

    //t - fn
    Matrix toNegate = valuesMatrices.back().negate();
    outputErrors = outputErrors.add(toNegate);

    //go back from the last
    for (int i = weightMatrices.size() - 1; i >= 0; i--) {
        Matrix toTranspose = weightMatrices[i].flipDimensions();
        //get the previous error
        Matrix prevErrors = outputErrors.mult(toTranspose);
        //store the derivative of the output
        Matrix derivatives = valuesMatrices[i + 1].operation(SIDMOID_DERIV);
        //multiply errors with derivatives to get gradients
        Matrix differences = outputErrors.elementWiseMultipy(derivatives);
        //alpha * error inf
        differences = differences.multScaler(alpha);
        //update using alpha * error * input
        Matrix weightDifferences = valuesMatrices[i].flipDimensions()
                .mult(differences);
        //now add weight differences to the weight
        weightMatrices[i] = weightMatrices[i].add(weightDifferences);
        //add the difference to the bias matrix (only alpha and err, not output)
        biasMatrices[i] = biasMatrices[i].add(differences);

        //to backpropagation
        // the errors
        outputErrors = prevErrors;
    }

}

std::vector<double> Network::getOutputValues() {
    return valuesMatrices.back().values;
}

string doubleToText(double d) {
    std::stringstream ss;
    ss << std::setprecision( 20 );
    ss << d << endl;
    return ss.str();
}

void Network::storeWeights() {
    ofstream myFile("storage.txt");

    for (int i = 0; i < weightMatrices.size(); i++)
        for (int x = 0; x < weightMatrices[i].rows; x++)
            for (int y = 0; y < weightMatrices[i].cols; y++) {
                myFile << doubleToText(weightMatrices[i].get(x, y));
                cout << setprecision(20) << weightMatrices[i].get(x, y) << endl;
            }

    myFile.close();
}

void Network::loadWeights() {
    ifstream myFile("storage.txt");
    string line;

    for (int i = 0; i < weightMatrices.size(); i++)
        for (int x = 0; x < weightMatrices[i].rows; x++)
            for (int y = 0; y < weightMatrices[i].cols; y++) {
                double d;
                myFile >> d;
                cout << d << endl;
                weightMatrices[i].get(x, y) = d;
            }

    myFile.close();
}

