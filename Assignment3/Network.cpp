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
                    static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.05)) + 0.005
            };
            row.push_back(c);
        }
        connections.push_back(row);
    }

    //push back as many bias values as there are columns
    for (int i = 0; i < cols; i++)
        this->biasWeights.push_back(0);

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
                    cout << ", ";
            }
        }

    for (double b : biasWeights)
        cout << "b" << b << " ";

    cout << "]" << endl;

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

vector<double>& ConnectionRow::getBiasWeights() {
    return this->biasWeights;
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

void Network::storeErrorTerms() {
    //store in the last nodes, then propagate backwards

    for (int i = 0; i < targetVals.size(); i++) {
        //difference = target - fn
        double fn = neurons[neurons.size() - 1][i].fn;
        double difference = targetVals[i] - fn;
        neurons[neurons.size() - 1][i].errorTerm = fn * (1 - fn) * (difference);
        neurons[neurons.size() - 1][i].biasErrorTerm = alpha * neurons[neurons.size() - 1][i].errorTerm;
    }
}

void Network::backPropagateErrors() {

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
            double sumOfOnlyErrorTerms = 0;

            for (int nextNeuron = 0; nextNeuron < neurons[layerNumber + 1].size(); nextNeuron++) { //cols = nuerons in next, rows = neurons in prev
                //add: errCorrNext * weightToCurr
                sumOfWeightsAndErrorTerms += neurons[layerNumber + 1][nextNeuron].errorTerm *
                                             connections[layerNumber].getWeight(currNeuron, nextNeuron);
                sumOfOnlyErrorTerms += neurons[layerNumber + 1][nextNeuron].errorTerm;
            }

            cout << "setting layer " << layerNumber << " neuron " << currNeuron << " error to " << sumOfWeightsAndErrorTerms << endl;
            //set the current neuron's error term to the sum
            neurons[layerNumber][currNeuron].errorTerm = sumOfWeightsAndErrorTerms;
            neurons[layerNumber][currNeuron].biasErrorTerm = sumOfOnlyErrorTerms;
        }

    }

}

void Network::correctWeights() {
    //loop back from the second last layer
    for (int i = neurons.size() - 2; i >= 0; i--) {
        cout << "correct weights from layer " << i << " to layer " << i + 1 << endl;

        //loop through the weights
        for (int col = 0; col < connections[i].getNumCols(); col++)
            for (int row = 0; row < connections[i].getNumRows(); row++) {
                double prevWeight = connections[i].getWeight(row, col);

                //next neuron's error term
                double deltaWeight = alpha * neurons[i + 1][col].errorTerm;

                //my fn
                if (i == 0) //input layer
                    //deltaWeight = alpha * errorOfNext * inputValue
                    deltaWeight *= inputVals[row];
                else
                    //deltaWeight = alpha * errorOfNext * myFn
                    deltaWeight *= neurons[i][col].fn;

                connections[i].setWeight(row, col, prevWeight + deltaWeight);

                //now correct the bias for this layer using error terms stored in biasErrorTerm for each neuron
                connections[i].getBiasWeights()[row] += deltaWeight; //not times input
            }
    }

}

void Network::backPropagate() {

    cout << "input vals: " << endl;
    for (double val : inputVals)
        cout << val << " ";
    cout << endl;

    cout << "backpropagating..." << endl;

    storeErrorTerms(); //error terms are now in the last nodes
    backPropagateErrors(); //all the error correction terms are set for each node
    correctWeights();

    print();

}

void Network::feedForward() {
    if (targetVals.empty())
        throw "Target vals is empty";
    if (inputVals.empty())
        throw "Input vals is empty";

    //set the values in the first neurons
    for (int i = 0; i < neurons[0].size(); i++)
        neurons[0][i] = sigmoid(inputVals[i]);

    for (int layerNumber = 1; layerNumber < neurons.size(); layerNumber++)
        for (int neuronTo= 0; neuronTo < neurons[layerNumber].size(); neuronTo++) {
            double value = 0;
            for (int neuronFrom = 0; neuronFrom < neurons[layerNumber - 1].size(); neuronFrom++) {
                value += connections[layerNumber - 1].getWeight(neuronFrom, neuronTo) *
                         neurons[layerNumber - 1][neuronFrom].fn;
            }

            value += connections[layerNumber - 1].getBiasWeights()[neuronTo];

            neurons[layerNumber][neuronTo] = sigmoid(value);
        }

}

void Network::testNetwork() {
    cout << "=================== TESTING NETWORK ====================" << endl;

    cout << "for inputs: ";
    vector<double>::iterator iter;
    for (iter = inputVals.begin(); iter != inputVals.end(); iter++)
        cout << *iter << " ";
    cout << endl;

    cout << "and target vals: ";
    for (iter = targetVals.begin(); iter != targetVals.end(); iter++)
        cout << *iter << " ";
    cout << endl;


    cout << "got output: ";
    std::vector<Neuron>::iterator neuronIter;
    for (neuronIter = neurons[neurons.size() - 1].begin(); neuronIter != neurons[neurons.size() - 1].end(); neuronIter++)
        cout << neuronIter->fn<< " ";

    cout << endl;

    cout << "========================================================" << endl;
}
