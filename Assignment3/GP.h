#pragma  once
#include <vector>
#include <string>
#include <list>
#include "sharedTypes.h"

enum entryNames {
    RECURRENT,
    AGE,
    MATURITY,
    MATURED_BY,
    WEEKS,
    IS_MALIG,
    SIZE,
    SIDE,
    SPECIFIC_SIDE,
    POSITIVE
};

struct entropyEntry {
    entryNames name;
    double entropy;
};

struct recurrentCounter {
    int nonrecurrentPos;
    int nonrecurrentNeg;
    int recurrentPos;
    int recurrentNeg;
};

struct ageCounter {
    int age_20Pos;
    int age_30Pos;
    int age_40Pos;
    int age_50Pos;
    int age_60Pos;
    int age_70Pos;

    int age_20Neg;
    int age_30Neg;
    int age_40Neg;
    int age_50Neg;
    int age_60Neg;
    int age_70Neg;
};

struct maturityCounter {
    int premenoPos;
    int gen40Pos;
    int lt40Pos;

    int premenoNeg;
    int gen40Neg;
    int lt40Neg;
};

struct maturedByCounter {
    int m0to4Pos;
    int m5to9Pos;
    int m10to14Pos;
    int m15to19Pos;
    int m20to24Pos;
    int m25to29Pos;
    int m30to34Pos;
    int m35to39Pos;
    int m40to44Pos;
    int m45to49Pos;
    int m50to54Pos;

    int m0to4Neg;
    int m5to9Neg;
    int m10to14Neg;
    int m15to19Neg;
    int m20to24Neg;
    int m25to29Neg;
    int m30to34Neg;
    int m35to39Neg;
    int m40to44Neg;
    int m45to49Neg;
    int m50to54Neg;
};

struct weeksCounter {
    int w0to2Pos;
    int w3to5Pos;
    int w6to8Pos;
    int w9to11Pos;
    int w12to14Pos;
    int w15to17Pos;
    int w24to25Pos;

    int w0to2Neg;
    int w3to5Neg;
    int w6to8Neg;
    int w9to11Neg;
    int w12to14Neg;
    int w15to17Neg;
    int w24to25Neg;
};

struct isMaligCounter {
    int yesPos;
    int noPos;
    int unknownPos;

    int yesNeg;
    int noNeg;
    int unknownNeg;
};

struct sizeCounter {
    int s1Pos;
    int s2Pos;
    int s3Pos;

    int s1Neg;
    int s2Neg;
    int s3Neg;
};

struct sideCounter {
    int leftPos;
    int rightPos;

    int leftNeg;
    int rightNeg;
};

struct specificSideCounter {
    int left_lowPos;
    int left_upPos;
    int right_lowPos;
    int right_upPos;
    int centralPos;
    int unknownPos;

    int left_lowNeg;
    int left_upNeg;
    int right_lowNeg;
    int right_upNeg;
    int centralNeg;
    int unknownNeg;
};

struct positiveCounter {
    int yes;
    int no;
};

class Node;

struct connection {
    Node* nextNode;
    std::string parameter;
};

class Node {
private:
    entryNames nodeName;
    std::vector<connection> connections;
    bool isLeaf;
    bool value;
public:
    Node(entryNames name);
    Node* getChild(std::string parameter);
    entryNames getName();
    void setAsLeaf();
    void setName(entryNames newName);
    void setValue(bool value);
    std::vector<connection>& getConnections();
};

class Tree {
private:
    int maxDepth;
    std::vector<dataInstace> instances;

    //counters to calculate entropy
    recurrentCounter recCounter;
    ageCounter aCounter;
    maturityCounter matCounter;
    maturedByCounter matByCounter;
    weeksCounter weekCounter;
    isMaligCounter maligCounter;
    sizeCounter szCounter;
    sideCounter sdCounter;
    specificSideCounter specificCounter;
    positiveCounter posCounter;

    Node* root;

    double getEntropy(std::vector<int> values);
    entryNames getLowestEntropy(std::vector<dataInstace> instances);
    std::vector<std::string> getParameterSet(Node* node);

public:
    //initialise with all the rows
    Tree(int maxDepth, std::vector<dataInstace>);
    std::vector<entropyEntry> calculateEntropy(std::vector<dataInstace> filteredInstances);
    void print();
};