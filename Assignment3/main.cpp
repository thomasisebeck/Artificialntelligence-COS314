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

    vector<double> inputVals;
    myNet.feedForward(inputVals);

    vector<double> targetVals;
    myNet.backProp(targetVals);

    vector<double> resultVals;
    myNet.getResults(resultVals);

    return 0;
}