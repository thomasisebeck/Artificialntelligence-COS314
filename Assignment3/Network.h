#include <vector>

class Neuron{};
typedef std::vector<Neuron> Layer;

class Network {
private:
    //2D vecotr
    std::vector<Layer> layers;
public:
    Network(std::vector<int> topology);
    void feedForward(const std::vector<double>& inputVals)





    void backProp(const std::vector<double>& targetVals);
    void getResults(std::vector<double>& inputVals) const;
};