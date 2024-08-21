#pragma once
#include <unordered_map>
#include <string>
#include "Node.h"
#include <vector>

class DecisionTree {
protected:
    std::vector<std::string> attributes;
public:
    std::unordered_map<std::string, std::vector<std::string>> mapLabels;

    DecisionTree(std::vector<std::string> attribtes, std::vector<std::string> data);


};