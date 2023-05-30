#include "Network.h"
#include <iostream>
#include <cmath>
using namespace std;

Network::Network(std::vector<int> topology) {
    for (int i = 0; i < topology.size(); i++) {
        //add the layer (the column)
        layers.push_back(Layer());

        //outputs = number of neurons in the next layer
        int numberOfOutputs;
        if (i == topology.size() - 1) //last layer, no outputs
            numberOfOutputs = 0;
        else
            numberOfOutputs = topology[i + 1];



        //add the neurons in the layer
        for (int neuron = 0; neuron <= topology[i]; neuron++) {
            //append to the most recently added layer
            layers.back().push_back(Neuron(numberOfOutputs, neuron));
            cout << "Made a neuron" << endl;
        }
    }
}

void Network::feedForward(const std::vector<double> &inputVals) {
    //number of input values has to be equal to number of input neurons
    if (inputVals.size() != layers[0].size() - 1)
        throw "Number of input values != number of input neurons";


    //set the values in the first layer
    for (int i = 0; i < inputVals.size(); i++) {
        layers[0][i].setOutputValue(inputVals[i]);
    }

    //propagate forward on each neuron in each layer to the next layer
    for (int layerNum = 1; layerNum < layers.size(); layerNum++) {
        Layer &prevLayer = layers[layerNum - 1];
        for (int j = 0; j < layers[layerNum].size() - 1; j++)
            layers[layerNum][j].feedForward(prevLayer);
    }
}

void Network::backProp(const std::vector<double>& targetVals) {

    //cacluate entire network error (RMS)
    Layer& outputLayer = layers.back();

    totalError = 0;

    for (int i = 0; i < outputLayer.size() - 1; i++) {
        double delta = targetVals[i] - outputLayer[i].getOutputValue();
        totalError += delta * delta;
    }

    totalError /= outputLayer.size() - 1; //average
    totalError = sqrt(totalError); //RMS

    //to see how well NN is peforming
    recentAverageError = (recentAverageError * recentAverageSmoothingFactor + totalError)
            / (recentAverageSmoothingFactor + 1);

    cout << "output layer size: " << outputLayer.size() << endl;
    cout << "target vals size: " << targetVals.size() << endl;
    //calculate output layer delta
    for (int i = 0; i < outputLayer.size(); i++) {
        outputLayer[i].calculateOutputGradients(targetVals[i]);
    }

    //calculate gradients of hidden layers
    for (int layerNum = layers.size() - 2; layerNum > 0; --layerNum) {
        Layer& hiddenLayer = layers[layerNum];
        Layer& nextLayer = layers[layerNum + 1];

        for (int i = 0; i < hiddenLayer.size(); i++)
            hiddenLayer[i].calculateHiddenGradients(nextLayer);
    }

    //update weights

    for (int layerNum = layers.size() - 1; layerNum > 0; --layerNum) {
        Layer& layer = layers[layerNum];
        Layer& prevLayer = layers[layerNum - 1];

        for (int i = 0; i < layers.size(); i++) {
            layer[i].updateInputWeights(prevLayer);
        }
    }
}

void Network::getResults(std::vector<double> &resultVals) const {
    resultVals.clear();

    for (int i = 0; i < layers.back().size() - 1; i++) {
        cout << layers.back()[0].getOutputValue() << endl;
        cout << layers.back()[1].getOutputValue() << endl;
        resultVals.push_back(layers.back()[i].getOutputValue());
    }
}