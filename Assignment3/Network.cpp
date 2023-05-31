#include "Network.h"
#include <iostream>
using namespace std;

ConnectionRow::ConnectionRow(int rows, int cols, string layer) {
    for (int i = 0; i < rows; i++) {
        vector<Connection> row;
        for (int j = 0; j < cols; j++) {
            Connection c {
                    "r" + to_string(i) + "c" + to_string(j),
                    1
            };
            row.push_back(c);
        }
        connections.push_back(row);
    }
    this->layer = layer;

    Connection c{
            "b_" + layer,
            1
    };

    this->biasConnection = c;

}



void ConnectionRow::printConnections() {
    cout << "trying to print..." << endl;
    cout << "Connections for layer " << layer << endl;
    vector<vector<Connection>>::iterator outerIter;
    vector<Connection>::iterator innerIter;

    if (!connections.empty())
        for (outerIter = connections.begin(); outerIter != connections.end(); outerIter++) {
            cout << "[";
            for (innerIter = (*outerIter).begin(); innerIter != (*outerIter).end(); innerIter++) {
                cout << innerIter->id << " w" << innerIter->weight;
                if (innerIter != (*outerIter).end() - 1)
                    cout << ", ";
            }
            cout << "]" << endl;
        }
    cout << "Bias value: ";
    cout << this->biasConnection.weight << endl;
    cout << endl;
}

double ConnectionRow::getWeight(int row, int col) {
    return connections[row][col].weight;
}
std::string ConnectionRow::getId(int row, int col) {
    return connections[row][col].id;
}

Connection &ConnectionRow::getBiasConnection() {
    return this->biasConnection;
}

Network::Network(vector<int> topology) {
    //create the neurons
    for (int i : topology) {
        vector<double> neuronCol;
        for (int j = 0; j < i; j++)
            neuronCol.push_back(0.5);
        neurons.push_back(neuronCol);
    }

    //create the connections
    for (int i = 0; i < topology.size() - 1; i++) {
        //rows = from
        int rows = topology[i];
        int cols = topology[i + 1];
        string layerName = to_string(i + 1) + "<->" + to_string(i + 2);

        connections.emplace_back(rows, cols, layerName);
    }


}

void Network::setInputVals(const vector<double> inputVals) {
    if (inputVals.size() != neurons[0].size())
        throw "Can't set input values if the size is not that same";
    this->inputVals = inputVals;
}

void Network::setTargetVals(const vector<double> targetVals) {
    this->targetVals = targetVals;
}

void Network::print() {
    //print neuron col, then connections...

    for (int i = 0; i < neurons.size(); i++) {
        cout << "Row : " << i + 1 << endl;
        for (int j = 0; j < neurons[i].size(); j++)
            cout << neurons[i][j] << " ";
        cout << endl;

        if (i != neurons.size() - 1)
            connections[i].printConnections();
    }

}

double ReLu(double x) {
    if (x >= 0)
        return x;
    return 0;
}

void Network::backPropagate() {
    //work out delta for output layer

}

void Network::feedForward() {
    if (targetVals.empty())
        throw "Target vals is empty";
    if (inputVals.empty())
        throw "Input vals is empty";

    //set the values in the first neurons
    for (int i = 0; i < neurons[0].size(); i++)
        neurons[0][i] = inputVals[i];

    cout << "input values set..." << endl;
    this->print();

    for (int layerNumber = 1; layerNumber < neurons.size(); layerNumber++) {
        //set the value in each neuron
        double newNeuronValue = 0;
        for (int neuronTo= 0; neuronTo < neurons[layerNumber].size(); neuronTo++) {
            double value = 0;
            for (int neuronFrom = 0; neuronFrom < neurons[layerNumber - 1].size(); neuronFrom++) {
                value += connections[layerNumber - 1].getWeight(neuronFrom, neuronTo) *
                         neurons[layerNumber - 1][neuronFrom];
            }
            value += connections[layerNumber - 1].getBiasConnection().weight;
            neurons[layerNumber][neuronTo] = ReLu(value);
        }
    }

    cout << "after one forward propagation..." << endl;
    this->print();
}
