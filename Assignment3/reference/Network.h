#pragma once
#include <vector>
#include "Neuron.h"

typedef std::vector<Neuron> Layer;

class Network {
private:
    //2D vecotr
    std::vector<Layer> layers;
    double totalError;
    double recentAverageError;
    double recentAverageSmoothingFactor;
public:
    Network(std::vector<int> topology);
    void feedForward(const std::vector<double>& inputVals);
    void backProp(const std::vector<double>& targetVals);
    void getResults(std::vector<double>& inputVals) const;
};