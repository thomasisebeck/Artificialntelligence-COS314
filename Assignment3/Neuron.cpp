#include "Neuron.h"
#include <iostream>
using namespace std;

Neuron::Neuron() {
    currentValue = 0;
}

void Neuron::setNextNeighbors(vector<Neuron*> nextNeighbors) {
    this->nextNeighbors = nextNeighbors;
}

void Neuron::setPrevNeighbors(std::vector<Neuron *> prevNeighbors) {
    this->prevNeighbors = prevNeighbors;
}

Neuron::~Neuron() {
    vector<Neuron*>::iterator iter;
    for (iter = nextNeighbors.begin(); iter != nextNeighbors.end(); iter++)
        delete (*iter);

    for (iter = prevNeighbors.begin(); iter != prevNeighbors.end(); iter++)
        delete (*iter);
}

void Neuron::printNeighbors() {
    cout << "previous: " << endl;
    vector<Neuron*>::iterator iter;
    for (iter = prevNeighbors.begin(); iter != prevNeighbors.end(); iter++)
        cout << (*iter)->currentValue << " ";
    cout << endl;
    cout << "next: " << endl;
    for (iter = nextNeighbors.begin(); iter != nextNeighbors.end(); iter++)
        cout << (*iter)->currentValue << " ";
    cout << endl;
}

void Neuron::setValue(float value) {
    this->currentValue = value;
}

float Neuron::getValue() {
    return currentValue;
}


