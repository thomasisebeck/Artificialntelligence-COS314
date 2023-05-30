#pragma once
#include <vector>

class Neuron {
private:
    float currentValue;
    std::vector<Neuron*> nextNeighbors;
    std::vector<Neuron*> prevNeighbors;
public:
    Neuron();
    void setNextNeighbors(std::vector<Neuron*> nextNeighbors);
    void setPrevNeighbors(std::vector<Neuron*> prevNeighbors);
    ~Neuron();
    void printNeighbors();
    void setValue(float value);
    float getValue();
};
