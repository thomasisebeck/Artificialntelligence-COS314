#include <vector>
#include <string>

struct Connection {
    std::string id;
    double weight;
};

class ConnectionRow {
private:
    std::vector<std::vector<Connection>> connections;
    std::string layer;
    int numRows;
    int numCols;
    std::vector<double> biasWeights; //added to each node in the calculation
public:
    ConnectionRow(int rows, int cols, std::string layer);
    void printConnections();
    double getWeight(int row, int col);
    void setWeight(int row, int col, double weight);
    std::string getId(int row, int col);
    int getNumRows();
    int getNumCols();
    std::vector<double>& getBiasWeights();
};

struct Neuron {
    double fn;
    double derivative;
    double errorTerm;
    double biasErrorTerm;
};

class Network {
private:
    //2D vector
    std::vector<std::vector<Neuron>> neurons;
    std::vector<double> currBiasErrorTerms;
    std::vector<double> targetVals;
    std::vector<double> inputVals;
    std::vector<ConnectionRow> connections;
    double alpha;
    void printConnectionsAt(int index);
    void backPropagateErrors();
    void correctWeights();
    void storeErrorTerms();
    ConnectionRow oldWeights;
public:
    Network(std::vector<int> topology, double alpha);
    void setInputVals(std::vector<double> inputVals);
    void setTargetVals(std::vector<double> targetVals);
    void testNetwork();
    void print();
    int getIsMalig();
    std::vector<double >getOutputValues();
    void feedForward();
    void backPropagate();
};