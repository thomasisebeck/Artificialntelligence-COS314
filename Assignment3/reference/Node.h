#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Node {
private:
    int depthRec(int depth);
public:
    std::string attribute;
    std::unordered_map<std::string, Node*> children;
    Node();
    Node(std::string attribute);
    Node(Node& ref);
    int getNumNodes();
    int getDepth();
    Node* getByAttr(std::string attribute);
    Node* getByLabel(std::string attr, std::string label);
    bool isLeaf();
    Node* getParent(Node* curr);
    bool hasChild(Node child);
    void addChild(std::string label, Node* child);
    bool hasLabel(std::string label);
};