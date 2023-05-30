#pragma once
#include <vector>

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron{
private:
    double outputValue;
    std::vector<Connection> outputWeights;
    double sumDOW(const Layer& nextLayer);
    int myIndex;
    double randomWeight();
    double gradient;
    static double eta;
    static double alpha;
public:
    Neuron(int numberOfOutputs, int myIndex);
    void setOutputValue(double value);
    double getOutputValue() const;
    void feedForward(const Layer& prevLayer);
    void calculateOutputGradients(double targetValue);
    void calculateHiddenGradients(const Layer& nextLayer);
    void updateInputWeights(Layer& prevLayer);
};