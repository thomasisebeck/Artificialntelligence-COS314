#include <vector>
#include <string>

struct Connection {
    std::string id;
    double weight;
};

class ConnectionRow {
public:
    std::vector<std::vector<Connection>> connections;
    std::string layer;
    int inputNodesCol_m;
    int outputNodesRow_j;
    std::vector<double> biasWeights; //added to each node in the calculation
public:
    ConnectionRow(int inputNodes, int outputNodes, std::string layer);
    void printConnections();
    double getWeight(int outNodesRowJ, int inNodesColM);
    void setWeight(int outNodesRowJ, int inNodesColM, double weight);
    std::string getId(int row, int col);
    int getNumInNodesCol_M();
    int getNumOutNodesRow_J();
    std::vector<double>& getBiasWeights();
};

struct Neuron {
    double fn;
    double derivative;
    double errorInformationTerm;
    double biasErrorTerm;
};

class Network {
private:
    //2D vector
    std::vector<std::vector<Neuron>> neurons;
    std::vector<double> currBiasErrorTerms;
    std::vector<double> targetVals;
    std::vector<double> inputVals;
    double alpha;
    void printConnectionsAt(int index);
    ConnectionRow oldWeights;
public:
    std::vector<ConnectionRow> connections;
    Network(std::vector<int> topology, double alpha);
    void setInputVals(std::vector<double> inputVals);
    void setTargetVals(std::vector<double> targetVals);
    void print();
    std::vector<double >getOutputValues();
    void feedForward();
    void backPropagate();
    void storeErrorTerms();
    void resetErrorTerms();
    bool correctWeights();
    void printOutputError();
};