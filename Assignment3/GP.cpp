#include "GP.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

using namespace std;

Node::Node(entryNames name) : nodeName(name) {
    this->isLeaf = false;
    connections.clear();
}

Node* Node::getChild(string parameter) {
    for (connection c : connections) {
        if (c.parameter == parameter)
            return c.nextNode;
    }

    return nullptr;
}

entryNames Node::getName() {
    return nodeName;
}

void Node::setAsLeaf() {
    this->isLeaf = true;
}

void Node::setName(entryNames newName) {
    this->nodeName = newName;
}

void Node::setValue(bool value) {
    this->value = value;
}

vector<connection> &Node::getConnections() {
    return this->connections;
}

vector<entropyEntry> Tree::calculateEntropy(vector<dataInstace> filteredInstances) {
    //calculate the entropy of each data value
    //store in entropy array

    vector<entropyEntry> entropy;

    //count the positive and negative values for each attribute
    recCounter = {0, 0, 0, 0 };
    aCounter = {0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0};
    matCounter = {0, 0, 0, 0, 0, 0};
    matByCounter = {0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0};
    weekCounter = {0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0};
    maligCounter = {0, 0, 0, 0, 0, 0};
    szCounter = {0, 0, 0, 0, 0, 0};
    sdCounter = {0, 0, 0, 0};
    specificCounter = {0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0};
    posCounter = {0, 0 };
    int totalCounter = 0;

    for (dataInstace d : filteredInstances) {
        totalCounter++;

        if (d.positive == 0) {
            posCounter.yes++;

            if (d.recurrent == 0) recCounter.recurrentPos++;
            else if (d.recurrent == 1) recCounter.nonrecurrentPos++;
            else throw "recurrent counter error";

            if (d.age == 0) aCounter.age_20Pos++;
            else if (d.age == 1) aCounter.age_30Pos++;
            else if (d.age == 2) aCounter.age_40Pos++;
            else if (d.age == 3) aCounter.age_50Pos++;
            else if (d.age == 4) aCounter.age_60Pos++;
            else if (d.age == 5) aCounter.age_70Pos++;
            else throw "age counter error";

            if (d.maturity == 0) matCounter.premenoPos++;
            else if (d.maturity == 1) matCounter.gen40Pos++;
            else if (d.maturity == 2) matCounter.lt40Pos++;
            else throw "maturity counter error";

            if (d.maturedBy == 0) matByCounter.m0to4Pos++;
            else if (d.maturedBy == 1) matByCounter.m5to9Pos++;
            else if (d.maturedBy == 2) matByCounter.m10to14Pos++;
            else if (d.maturedBy == 3) matByCounter.m15to19Pos++;
            else if (d.maturedBy == 4) matByCounter.m20to24Pos++;
            else if (d.maturedBy == 5) matByCounter.m25to29Pos++;
            else if (d.maturedBy == 6) matByCounter.m30to34Pos++;
            else if (d.maturedBy == 7) matByCounter.m35to39Pos++;
            else if (d.maturedBy == 8) matByCounter.m40to44Pos++;
            else if (d.maturedBy == 9) matByCounter.m45to49Pos++;
            else if (d.maturedBy == 10) matByCounter.m50to54Pos++;
            else throw "matured by counter error";

            if (d.weeks == 0) weekCounter.w0to2Pos++;
            else if (d.weeks == 1) weekCounter.w3to5Pos++;
            else if (d.weeks == 2) weekCounter.w6to8Pos++;
            else if (d.weeks == 3) weekCounter.w9to11Pos++;
            else if (d.weeks == 4) weekCounter.w12to14Pos++;
            else if (d.weeks == 5) weekCounter.w15to17Pos++;
            else if (d.weeks == 6) weekCounter.w24to25Pos++;
            else throw "weeks counter error";

            if (d.isMalig == 0) maligCounter.yesPos++;
            else if (d.isMalig == 1) maligCounter.noPos++;
            else if (d.isMalig == 2) maligCounter.unknownPos++;
            else throw "is malig counter error";

            if (d.size == 0) szCounter.s1Pos++;
            else if (d.size == 1) szCounter.s2Pos++;
            else if (d.size == 2) szCounter.s3Pos++;
            else throw "size counter error";

            if (d.side == 0) sdCounter.leftPos++;
            else if (d.side == 1) sdCounter.rightPos++;
            else throw "side counter error";

            if (d.specificSide == 0) specificCounter.left_lowPos++;
            else if (d.specificSide == 1) specificCounter.left_upPos++;
            else if (d.specificSide == 2) specificCounter.right_lowPos++;
            else if (d.specificSide == 3) specificCounter.right_lowPos++;
            else if (d.specificSide == 4) specificCounter.right_upPos++;
            else if (d.specificSide == 5) specificCounter.centralPos++;
            else if (d.specificSide == 6) specificCounter.unknownPos++;
            else throw "specific side counter error";

        } else { //not positive
            posCounter.no++;

            if (d.recurrent == 0) recCounter.recurrentNeg++;
            else if (d.recurrent == 1) recCounter.nonrecurrentNeg++;
            else throw "recurrent counter error";

            if (d.age == 0) aCounter.age_20Neg++;
            else if (d.age == 1) aCounter.age_30Neg++;
            else if (d.age == 2) aCounter.age_40Neg++;
            else if (d.age == 3) aCounter.age_50Neg++;
            else if (d.age == 4) aCounter.age_60Neg++;
            else if (d.age == 5) aCounter.age_70Neg++;
            else throw "age counter error";

            if (d.maturity == 0) matCounter.premenoNeg++;
            else if (d.maturity == 1) matCounter.gen40Neg++;
            else if (d.maturity == 2) matCounter.lt40Neg++;
            else throw "maturity counter error";

            if (d.maturedBy == 0) matByCounter.m0to4Neg++;
            else if (d.maturedBy == 1) matByCounter.m5to9Neg++;
            else if (d.maturedBy == 2) matByCounter.m10to14Neg++;
            else if (d.maturedBy == 3) matByCounter.m15to19Neg++;
            else if (d.maturedBy == 4) matByCounter.m20to24Neg++;
            else if (d.maturedBy == 5) matByCounter.m25to29Neg++;
            else if (d.maturedBy == 6) matByCounter.m30to34Neg++;
            else if (d.maturedBy == 7) matByCounter.m35to39Neg++;
            else if (d.maturedBy == 8) matByCounter.m40to44Neg++;
            else if (d.maturedBy == 9) matByCounter.m45to49Neg++;
            else if (d.maturedBy == 10) matByCounter.m50to54Neg++;
            else throw "matured by counter error";

            if (d.weeks == 0) weekCounter.w0to2Neg++;
            else if (d.weeks == 1) weekCounter.w3to5Neg++;
            else if (d.weeks == 2) weekCounter.w6to8Neg++;
            else if (d.weeks == 3) weekCounter.w9to11Neg++;
            else if (d.weeks == 4) weekCounter.w12to14Neg++;
            else if (d.weeks == 5) weekCounter.w15to17Neg++;
            else if (d.weeks == 6) weekCounter.w24to25Neg++;
            else throw "weeks counter error";

            if (d.isMalig == 0) maligCounter.yesNeg++;
            else if (d.isMalig == 1) maligCounter.noNeg++;
            else if (d.isMalig == 2) maligCounter.unknownNeg++;
            else throw "is malig counter error";

            if (d.size == 0) szCounter.s1Neg++;
            else if (d.size == 1) szCounter.s2Neg++;
            else if (d.size == 2) szCounter.s3Neg++;
            else throw "size counter error";

            if (d.side == 0) sdCounter.leftNeg++;
            else if (d.side == 1) sdCounter.rightNeg++;
            else throw "side counter error";

            if (d.specificSide == 0) specificCounter.left_lowNeg++;
            else if (d.specificSide == 1) specificCounter.left_upNeg++;
            else if (d.specificSide == 2) specificCounter.right_lowNeg++;
            else if (d.specificSide == 3) specificCounter.right_lowNeg++;
            else if (d.specificSide == 4) specificCounter.right_upNeg++;
            else if (d.specificSide == 5) specificCounter.centralNeg++;
            else if (d.specificSide == 6) specificCounter.unknownNeg++;
            else throw "specific side counter error";
        }

    }

    vector<int> recurrentEntropy {
            recCounter.recurrentPos, recCounter.recurrentNeg,
            recCounter.nonrecurrentPos, recCounter.nonrecurrentNeg
    };
    entropy.push_back({
        RECURRENT,
        getEntropy(recurrentEntropy)
    });

    vector<int> ageEntropy = {
            aCounter.age_20Pos, aCounter.age_20Neg,
            aCounter.age_30Pos, aCounter.age_30Neg,
            aCounter.age_40Pos, aCounter.age_40Neg,
            aCounter.age_50Pos, aCounter.age_50Neg,
            aCounter.age_60Pos, aCounter.age_60Neg,
            aCounter.age_70Pos, aCounter.age_70Neg
    };
    entropy.push_back({
        AGE,
        getEntropy(ageEntropy)
    });

    vector<int> maturityEntropy = {
            matCounter.premenoPos, matCounter.premenoNeg,
            matCounter.gen40Pos, matCounter.gen40Neg,
            matCounter.lt40Pos, matCounter.lt40Neg,
    };
    entropy.push_back({
        MATURITY,
        getEntropy(maturityEntropy)
    });

    vector<int> maturedByEntropy = {
            matByCounter.m0to4Pos, matByCounter.m0to4Neg,
            matByCounter.m5to9Pos, matByCounter.m5to9Neg,
            matByCounter.m10to14Pos, matByCounter.m10to14Neg,
            matByCounter.m15to19Pos, matByCounter.m15to19Neg,
            matByCounter.m20to24Pos, matByCounter.m20to24Neg,
            matByCounter.m25to29Pos, matByCounter.m25to29Neg,
            matByCounter.m30to34Pos, matByCounter.m30to34Neg,
            matByCounter.m35to39Pos, matByCounter.m35to39Neg,
            matByCounter.m40to44Pos, matByCounter.m40to44Neg,
            matByCounter.m45to49Pos, matByCounter.m45to49Neg,
            matByCounter.m50to54Pos, matByCounter.m50to54Neg
    };
    entropy.push_back({
         MATURED_BY,
         getEntropy(maturedByEntropy)
    });

    vector<int> weeksEntropy = {
            weekCounter.w0to2Pos, weekCounter.w0to2Neg,
            weekCounter.w3to5Pos, weekCounter.w3to5Neg,
            weekCounter.w6to8Pos, weekCounter.w6to8Neg,
            weekCounter.w9to11Pos, weekCounter.w9to11Neg,
            weekCounter.w12to14Pos, weekCounter.w12to14Neg,
            weekCounter.w15to17Pos, weekCounter.w15to17Neg,
            weekCounter.w24to25Neg, weekCounter.w24to25Neg
    };
    entropy.push_back({
        WEEKS,
        getEntropy(weeksEntropy)
    });

    vector<int> isMaligEntropy = {
            maligCounter.unknownPos, maligCounter.unknownNeg,
            maligCounter.noPos, maligCounter.noNeg,
            maligCounter.yesPos, maligCounter.yesNeg
    };
    entropy.push_back({
        IS_MALIG,
        getEntropy(isMaligEntropy)
    });

    vector<int> sizeEntropy = {
            szCounter.s1Pos, szCounter.s1Neg,
            szCounter.s2Pos, szCounter.s2Neg,
            szCounter.s3Pos, szCounter.s3Neg
    };
    entropy.push_back({
        SIZE,
        getEntropy(sizeEntropy)
    });

    vector<int> sideEntropy = {
            sdCounter.leftPos, sdCounter.leftNeg,
            sdCounter.rightPos, sdCounter.rightNeg
    };
    entropy.push_back({
        SIDE,
        getEntropy(sideEntropy)
    });

    vector<int> specificEntropy = {
            specificCounter.left_lowPos, specificCounter.left_lowNeg,
            specificCounter.left_upPos, specificCounter.left_upNeg,
            specificCounter.right_lowPos, specificCounter.right_lowNeg,
            specificCounter.right_upPos, specificCounter.right_upNeg,
            specificCounter.centralPos, specificCounter.centralNeg,
            specificCounter.unknownPos, specificCounter.unknownNeg
    };
    entropy.push_back({
        SPECIFIC_SIDE,
        getEntropy(specificEntropy)
    });

    vector<int> positiveEntropy = {posCounter.yes, posCounter.no };
    entropy.push_back({
        POSITIVE,
        getEntropy(positiveEntropy)
    });

    return entropy;

}

entryNames Tree::getLowestEntropy(vector<dataInstace> instances) {
    vector<entropyEntry> currentEntropies = this->calculateEntropy(instances);

    double lowest = currentEntropies[0].entropy;
    entryNames lowestName = currentEntropies[0].name;

    for (entropyEntry entry : currentEntropies) {
        if (entry.entropy < lowest) {
            if (entry.name != POSITIVE) {
                lowest = entry.entropy;
                lowestName = entry.name;
            };
        }
    }

    return lowestName;
}

string translateName(entryNames name) {
    if (name == RECURRENT)
        return "RECURRENT";
    if (name == AGE)
        return "AGE";
    if (name == MATURITY)
        return "MATURITY";
    if (name == MATURED_BY)
        return "MATURED_BY";
    if (name == WEEKS)
        return "WEEKS";
    if (name == IS_MALIG)
        return "IS_MALIG";
    if (name == SIZE)
        return "SIZE";
    if (name == SIDE)
        return "SIDE";
    if (name == SPECIFIC_SIDE)
        return "SPECIFIC_SIDE";
    if (name == POSITIVE)
        return "POSITIVE";

    cout << "Error for name : " << name << endl;
    throw "could not find name";
}

Node* addBranches(vector<entryNames> usedNames, vector<dataInstace> instances) {
    //if every attribute in the data set results in yes or no, return a new node
    //

}

Tree::Tree(int maxDepth, vector<dataInstace> instances) {

    this->maxDepth = maxDepth;

    //create the root node before you can branch, get the lowest entropy for this
    entryNames lowest = getLowestEntropy(instances);

    this->root = new Node(lowest);

    vector<entryNames> usedNames;
    usedNames.push_back(lowest);

   // addBranches(root, usedNames, 1, maxDepth);

}

void recPrint(Node* currNode) {
    if (currNode == nullptr)
        return;
    if (currNode->getConnections().size() == 0)
        return;

    cout << "name: " << translateName(currNode->getName()) << endl;
    cout << "children: " << endl;

    for (connection c: currNode->getConnections()) {
        cout << "  " << c.parameter << endl;
    }

    for (connection c: currNode->getConnections())
            recPrint(c.nextNode);
}

void Tree::print() {
    recPrint(this->root);
}

double Tree::getEntropy(vector<int> values) {

    if (values.size() % 2 != 0)
        throw "values size is not divisible by 2";

    double entropy = 0;

    for (int i = 0; i < values.size(); i += 2) {
        int total = values[i] + values[i + 1];
        double pos = static_cast<double>(values[i]) / total;
        double neg = static_cast<double>(values[i + 1]) / total;
        entropy += - pos * log2(pos);
        entropy += - neg * log2(neg);
    }

    return entropy;
}

vector<string> Tree::getParameterSet(Node *node) {
    entryNames name = node->getName();


    switch (name) {
        case RECURRENT:
            return {
                "nonrecurrent",
                "recurrent"
            };
        case AGE:
            return {
                "20",
                "30",
                "40",
                "50",
                "60",
                "70",
            };

        case MATURITY:
            return {
                "premeno",
                "gen40",
                "lt40"
            };

        case MATURED_BY:
            return {
                "m0to4",
                "m5to9",
                "m10to14",
                "m15to19",
                "m20to24",
                "m25to29",
                "m30to34",
                "m35to39",
                "m40to44",
                "m45to49",
                "m50to54",
            };

        case WEEKS:

            return {
                   "0to2",
                   "3to5",
                   "6to8",
                   "9to11",
                   "12to14",
                   "15to17",
                   "24to25",
            };

        case IS_MALIG:

            return {
                "yes",
                "no",
                "unknown",
            };

        case SIZE:

            return {
                "s1",
                "s2",
                "s3",
            };

        case SIDE:

            return {
                "left",
                "right"
            };

        case SPECIFIC_SIDE:

            return {
                "left_low",
                "left_up",
                "right_low",
                "right_up",
                "central",
                "unknown",
            };

        case POSITIVE:

            return {
                "yes",
                "no"
            };
    }
}
