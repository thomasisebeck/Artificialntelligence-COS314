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

Network::Network(vector<int> topology, double alpha) : oldWeights(0,0,"empty") {
    //create the neurons
    for (int i : topology) {
        vector<Neuron> neuronCol;
        for (int j = 0; j < i; j++)
            neuronCol.push_back({0.5, 0, 0});
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

    this->alpha = alpha;

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
            cout << "fn(" << neurons[i][j].fn << "), deriv(" << neurons[i][j].derivative << "), err(" << neurons[i][j].errorTerm << ") ";
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
    return { function , deriv, x };
}

Neuron sigmoid(double x) {
    double function = static_cast<double>(1) / (1 + exp(-x));
    double deriv = function * (1 - function);
    return { function, deriv, x };
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
                                  connections[index].getNumCols(), "weights copy");
    for (int row = 0; row < connections[index].getNumRows(); row++)
        for (int col = 0; col < connections[index].getNumCols(); col++)
            oldOuputWeights.setWeight(row, col, connections[index].getWeight(row, col));

    //----------------------------------------------------------------------//

    return oldOuputWeights;
}

void Network::storeErrorTerms() {
    //store in the last nodes, then propagate backwards

    for (int i = 0; i < targetVals.size(); i++) {
        //difference = target - fn
        double fn = neurons[neurons.size() - 1][i].fn;
        double difference = targetVals[i] - fn;
        neurons[neurons.size() - 1][i].errorTerm = fn * (1 - fn) * (difference);
    }
}
void Network::backPropagate() {

    cout << "backpropagating..." << endl;

    storeErrorTerms(); //error terms are now in the last nodes

    print();

    //now backpropagate these error correction terms using the existing weights
    for (int layerNumber = neurons.size() - 2; layerNumber >= 0; layerNumber--) {
        cout << "Backprop to layer " << layerNumber << endl;

        //store the error terms in each of the nodes
        //it's the sum of the error correction terms from the output * weights

        //bias CorrTerm = learning rate * errorTermForThatNode

        //loop through the previous layer nodes
        //delta = f(n) * (1 - f(n)) * sum(weight_to_next_node * errorTermOfNextNodes)
        for (int currNeuron = 0; currNeuron < neurons[layerNumber].size(); currNeuron++) {
            double sumOfWeightsAndErrorTerms = 0;

            for (int nextNeuron = 0; nextNeuron < neurons[layerNumber + 1].size(); nextNeuron++) { //cols = nuerons in next, rows = neurons in prev
                //add: errCorrNext * weightToCurr
                sumOfWeightsAndErrorTerms += neurons[layerNumber + 1][nextNeuron].errorTerm *
                                             connections[layerNumber].getWeight(currNeuron, nextNeuron);
                cout << "adding: " << neurons[layerNumber + 1][nextNeuron].errorTerm *
                                      connections[layerNumber].getWeight(currNeuron, nextNeuron)
                                      << " for current neuron " << currNeuron << endl;
            }

            //set the current neuron's error term to the sum
            neurons[layerNumber][currNeuron].errorTerm = sumOfWeightsAndErrorTerms;

        }

    }



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

}
