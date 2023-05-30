#include "Neuron.h"
#include <cmath>

Neuron::Neuron(int numberOfOutputs, int index) {
    for (int i = 0; i < numberOfOutputs; i++) {
        Connection c;
        c.weight = rand() / double(RAND_MAX);
        outputWeights.push_back(c);
    }

    myIndex = index;
    outputValue = 0;
}

void Neuron::setOutputValue(double value) {
    outputValue = value;
}

double Neuron::getOutputValue() const {
    return outputValue;
}

double Neuron::randomWeight() {
    return rand() / double(RAND_MAX);
}

double activate(double sum) {
    //use an activation
    //function is tanh: output range [-1, 1]

    return tanh(sum);
}

double transferActivation(double sum) {
    return 1.0 - sum * sum;
}

void Neuron::feedForward(const Layer &prev) {
    //sum up the inputs and use the activation function
    //to propagate it

    double sum = 0;

    for (int i = 0; i < prev.size(); i++) {
        sum += prev[i].getOutputValue() *
                prev[i].outputWeights[myIndex].weight;
    }

    outputValue = activate(sum);
}

void Neuron::calculateOutputGradients(double targetValue) {
    double delta = targetValue - outputValue;
    gradient = delta * transferActivation(outputValue);
}

void Neuron::updateInputWeights(Layer &prevLayer) {
    for (int i = 0; i < prevLayer.size(); i++) {
        Neuron& neuron = prevLayer[i];
        double oldDeltaWeight = neuron.outputWeights[myIndex].deltaWeight;

        //alpha = momentum
        //eta = learning rate
        double newDeltaWeight = eta * neuron.getOutputValue() * gradient
                + alpha * oldDeltaWeight;

        neuron.outputWeights[myIndex].deltaWeight = newDeltaWeight;
        neuron.outputWeights[myIndex].weight += newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer& nextLayer) {
    double sum = 0;

    for (int i = 0; i < nextLayer.size() - 1; i++) {
        sum += outputWeights[i].weight * nextLayer[i].gradient;
    }

    return sum;
}

void Neuron::calculateHiddenGradients(const Layer &nextLayer) {
    double dow = sumDOW(nextLayer);
    gradient = dow * transferActivation(outputValue);
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;
