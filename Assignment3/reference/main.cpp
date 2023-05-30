#include <iostream>
#include <vector>
#include "Network.h"
using namespace std;

int main() {

    //if we send in { 3, 2, 1 }
    //it is number of layers in input, hidden, output

    vector<int> topology;
    topology.push_back(3); //3 input layers
    topology.push_back(2); //2 hidden layers
    topology.push_back(1); //1 output layers
    Network myNet(topology);

    try {
        vector<double> inputVals = { 3, 5, 1};
        myNet.feedForward(inputVals);
    }
    catch (const char* err) {
        cout << err << endl;
    }

    cout << "fed forward..." << endl;

    vector<double> targetVals = { 1, 5 };
    myNet.backProp(targetVals);

    cout << "back prop done ..." << endl;

    vector<double> resultVals;
    myNet.getResults(resultVals);

    return 0;
}