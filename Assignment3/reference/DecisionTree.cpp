#include "DecisionTree.h"
#include <vector>
#include <string>
using namespace std;

DecisionTree::DecisionTree(std::vector<std::string> attribtes, std::vector<std::string> data) {
    this->attributes = attribtes;
    vector<string> emptyVector;
    for (string attr: attribtes)
        mapLabels.insert(make_pair(attr, emptyVector));

    for ()
}
