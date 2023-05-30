#include <vector>
#include "Neuron.h"

class Network {
private:
    //2D vector
    std::vector<std::vector<Neuron*>> layers;
public:
    Network(std::vector<int> topology);
    void feedForward(const std::vector<double>& inputVals);
    void backProp(const std::vector<double>& targetVals);
    void getResults(std::vector<double>& inputVals) const;
    void print() const;
};