#include "Network.h"

Network::Network(std::vector<int> topology) {
    for (int i = 0; i < topology.size(); i++) {
        //add the layer (the column)
        layers.push_back(Layer());

        //add the neurons in the layer
        for (int neuron = 0; neuron <= topology[i]; neuron++)
            //append to the most recently added layer
            layers.back().push_back(Neuron());
    }
}

void Network::feedForward(const std::vector<double> &inputVals) {

}

void Network::backProp(const std::vector<double> &targetVals) {

}

void Network::getResults(std::vector<double> &inputVals) const {

}