#include "Network.h"
#include <iostream>
using namespace std;

Network::Network(std::vector<int> topology) {
    for (int i = 0; i < topology.size(); i++) {
        std::vector<Neuron*> emptyLayer;
        //add the layer (the column)
        layers.push_back(emptyLayer);

        //add the neurons in the layer
        for (int neuron = 0; neuron <= topology[i]; neuron++)
            //append to the most recently added layer
            layers[i].push_back(new Neuron());

        if (i > 0) { //set previous neurons
            for (int j = 0; j < layers[i].size(); j++)
                layers[i][j]->setPrevNeighbors(layers[i-1]);
        }
    }

    //set the next neurons for each layer
    for (int i = 0; i < layers.size() - 1; i++) {
        for (int j = 0; j < layers[i].size(); j++)
            layers[i][j]->setNextNeighbors(layers[i + 1]);
    }
}

void Network::feedForward(const std::vector<double> &inputVals) {

}

void Network::backProp(const std::vector<double> &targetVals) {

}

void Network::print() const {
    int layerNumber = 1;
    for (std::vector<Neuron*> l : layers) {
        cout << "Layer: " << layerNumber << endl;
        for (Neuron* n : l) {
            cout << "value: " << n->getValue() << endl;
            n->printNeighbors();
        }
        cout << endl;
        layerNumber++;
    }
}
