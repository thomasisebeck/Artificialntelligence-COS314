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
    std::vector<Connection> biasConnections;
    int numRows;
    int numCols;
public:
    ConnectionRow(int rows, int cols, std::string layer);
    void printConnections();
    double getWeight(int row, int col);
    void setWeight(int row, int col, double weight);
    std::string getId(int row, int col);
    int getNumRows();
    int getNumCols();
    std::vector<Connection>& getBiasConnections();
};

struct Neuron {
    double fn;
    double derivative;
};

class Network {
private:
    //2D vector
    std::vector<std::vector<Neuron>> neurons;
    std::vector<double> targetVals;
    std::vector<double> inputVals;
    std::vector<ConnectionRow> connections;
    double alpha;
    void printConnectionsAt(int index);
    ConnectionRow getWeightsCopy(int index);
    void correctHiddenToOutputWeights();
public:
    Network(std::vector<int> topology, double alpha);
    void setInputVals(std::vector<double> inputVals);
    void setTargetVals(std::vector<double> targetVals);
    void print();
    void feedForward();
    void backPropagate();
};