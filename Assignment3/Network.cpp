#include "Network.h"
#include <iostream>
#include <cmath>
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

    for (int i = 0; i < cols; i++) {
        Connection c{
                "b_" + layer,
                0
        };

        this->biasConnections.push_back(c);
    }

    this->layer = layer;

    this->numCols = cols;
    this->numRows = rows;

}



void ConnectionRow::printConnections() {
    cout << "----------------------------------" << endl;
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
    cout << "Bias values: ";
    for (innerIter = biasConnections.begin(); innerIter != biasConnections.end(); innerIter++)
        cout << "[" << innerIter->id << " " << innerIter->weight << "]" << endl;
    cout << "----------------------------------" << endl;
}

double ConnectionRow::getWeight(int row, int col) {
    return connections[row][col].weight;
}

void ConnectionRow::setWeight(int row, int col, double weight) {
    connections[row][col].weight = weight;
}

std::string ConnectionRow::getId(int row, int col) {
    return connections[row][col].id;
}

int ConnectionRow::getNumCols() {
    return numCols;
}

int ConnectionRow::getNumRows() {
    return numRows;
}

vector<Connection>& ConnectionRow::getBiasConnections() {
    return this->biasConnections;
}

Network::Network(vector<int> topology, double alpha) : alpha(alpha) {
    //create the neurons
    for (int i : topology) {
        vector<Neuron> neuronCol;
        for (int j = 0; j < i; j++)
            neuronCol.push_back({0.5, 0});
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
            cout << "fn(" << neurons[i][j].fn << "), deriv(" << neurons[i][j].derivative << ") ";
        cout << endl;

        if (i != neurons.size() - 1)
            connections[i].printConnections();
    }

}

void Network::printConnectionsAt(int index) {
    cout << "---------- connections for " << index << " -------------" << endl;

    vector<Neuron> currentNeurons = neurons[index + 1];
    cout << "current neuron values: " << endl;
    vector<Neuron>::iterator iter;
    for (iter = currentNeurons.begin(); iter != currentNeurons.end(); iter++)
        cout << (*iter).fn << endl;

    for (int row = 0; row < connections[index].getNumRows(); row++) {
        cout << "[";
        for (int col = 0; col < connections[index].getNumCols(); col++)
            cout << connections[index].getWeight(row, col) << " ";
        cout << "]" << endl;
    }

    cout << "-------------------------------------------" << endl;
}

Neuron ReLu(double x) {
    double function = x >= 0 ? x : 0;
    double deriv = x >= 0 ? 1 : 0;
    return { function , deriv };
}

Neuron sigmoid(double x) {
    double function = static_cast<double>(1) / (1 + exp(-x));
    double deriv = function * (1 - function);
    return { function, deriv };
}

double calculateError(vector<double> targets, vector<double> outputs) {
    if (targets.size() != outputs.size())
        throw "Target size does not equal output size!";

    double sum = 0;
    for (int i = 0; i < targets.size(); i++) {
        double difference = targets[i] - outputs[i];
        sum += 0.5 * difference * difference;
    }

    return sum;
}

void printDoubleArray(vector<double> arr, string prompt) {
    cout << prompt << ": [ ";
    vector<double>::iterator iter;
    for (iter = arr.begin(); iter != arr.end(); iter++)
        cout << *iter << " ";
    cout << "]" << endl;
}

ConnectionRow Network::getWeightsCopy(int index) {
    if (index > connections.size() - 1 || index < 0)
        throw "invalid index to copy weights to";

    //------------------------ copy the output weights ---------------------//

    ConnectionRow oldOuputWeights(connections[index].getNumRows(),
                                  connections[index].getNumCols(), "outputOld");
    for (int row = 0; row < connections[index].getNumRows(); row++)
        for (int col = 0; col < connections[index].getNumCols(); col++)
            oldOuputWeights.setWeight(row, col, connections[index].getWeight(row, col));

    //----------------------------------------------------------------------//

    return oldOuputWeights;
}

void Network::correctHiddenToOutputWeights() {
    //copy the output weights
    ConnectionRow oldOuputWeights = getWeightsCopy(connections.size() - 1);

    //hidden to output error correction
    vector<Neuron> outputNeurons = neurons[neurons.size() - 1];
    const int OUTPUT_ROWS = connections[connections.size() - 1].getNumRows();
    const int OUTPUT_COLS = connections[connections.size() - 1].getNumCols();

    vector<double> outputErrors;
    vector<double> outputFns;
    for (int row = 0; row < OUTPUT_ROWS; row++)
        for (int col = 0; col < OUTPUT_COLS; col++) {
            double currentTarget = targetVals[col];
            double outputFn = neurons[neurons.size() - 1][col].fn;
            double outputDeriv = neurons[neurons.size() - 1][col].derivative;

            outputErrors.push_back(outputFn * outputDeriv * (currentTarget - outputFn));
            outputFns.push_back(outputFn);
        }

    int currErr = 0;
    //update output weights using the errors
    for (int row = 0; row < OUTPUT_ROWS; row++)
        for (int col = 0; col < OUTPUT_COLS; col++) {
            double oldWeight = connections[connections.size() - 1].getWeight(row, col);
            double newWeight = oldWeight + outputErrors[currErr];
            connections[connections.size() - 1].setWeight(row, col, newWeight);
            currErr++;
        }
}

void Network::backPropagate() {

    correctHiddenToOutputWeights();


    /*

    //-------------------------------- HIDDEN LAYERS ------------------------------//

    for (int layerNumber = connections.size() - 2; layerNumber >= 0; layerNumber--) {
        cout << "CORRECTING ON LAYER: " << layerNumber << endl;

        //sum backwards from the output that we got, to the previous layer
        vector<double> backwardsPropagatedInputs;

        for (int prevLayerNeuron = 0; prevLayerNeuron < neurons[layerNumber].size(); prevLayerNeuron++) {
            double currSum = 0;
            for (int nextLayerNeuron = 0; nextLayerNeuron < neurons[layerNumber + 1].size(); nextLayerNeuron++) {
                currSum += neurons[layerNumber + 1][nextLayerNeuron].fn *
                           oldOuputWeights.getWeight(nextLayerNeuron, prevLayerNeuron);
                double currFn = neurons[layerNumber][prevLayerNeuron].fn;
                double oldOutputWeight = oldOuputWeights.getWeight(prevLayerNeuron, nextLayerNeuron)
                        * errorInformationTermsPrev[nextLayerNeuron];
                currSum += (currFn) * (1 - currFn) * oldOutputWeight;
            }
            cout << "Summed outputs from output neurons to neuron " << prevLayerNeuron << " in prev layer: " << currSum << endl;


        }
    }*/

}

void Network::feedForward() {
    if (targetVals.empty())
        throw "Target vals is empty";
    if (inputVals.empty())
        throw "Input vals is empty";

    //set the values in the first neurons
    for (int i = 0; i < neurons[0].size(); i++)
        neurons[0][i] = ReLu(inputVals[i]);

    for (int layerNumber = 1; layerNumber < neurons.size(); layerNumber++)
        for (int neuronTo= 0; neuronTo < neurons[layerNumber].size(); neuronTo++) {
            double value = 0;
            for (int neuronFrom = 0; neuronFrom < neurons[layerNumber - 1].size(); neuronFrom++) {
                value += connections[layerNumber - 1].getWeight(neuronFrom, neuronTo) *
                         neurons[layerNumber - 1][neuronFrom].fn;
            }

            value += connections[layerNumber - 1].getBiasConnections()[neuronTo].weight;

            if (layerNumber == neurons.size() - 1)
                //TODO: change to sigmoid on final layer
                neurons[layerNumber][neuronTo] = ReLu(value);
            else
                neurons[layerNumber][neuronTo] = ReLu(value);
        }

    this->print();
}
