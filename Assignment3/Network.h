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
    double bias;
public:
    ConnectionRow(int rows, int cols, std::string layer);
    void printConnections();
    double getWeight(int row, int col);
    std::string getId(int row, int col);
};

class Network {
private:
    //2D vector
    std::vector<std::vector<double>> neurons;
    std::vector<double> targetVals;
    std::vector<double> inputVals;
    std::vector<ConnectionRow> connections;
public:
    Network(std::vector<int> topology);
    void setInputVals(std::vector<double> inputVals);
    void setTargetVals(std::vector<double> targetVals);
    void print();
    void feedForward();
    void backPropagate();
};