#include "Node.h"
#include <string>
using namespace std;

Node::Node() {
    this->attribute = "";
}

Node::Node(std::string attribute) {
    this->attribute = attribute;
}

Node::Node(Node &ref) {
    this->attribute = ref.attribute;

    std::unordered_map<string, Node*>::iterator iter;

    for(iter = ref.children.begin(); iter != children.end(); iter++)
    {
        string k =  iter->first;
        Node* n = iter->second;
        children.insert(make_pair(k, n));
    }
}

int Node::getNumNodes() {
    int numNodes = 1;
    if (isLeaf()) return numNodes;

    std::unordered_map<string, Node*>::iterator iter;

    for(iter = children.begin(); iter != children.end(); iter++) {
        Node* child = children.at(iter->first);
        if (child == nullptr) continue;
        numNodes += child->getNumNodes();
    }

    return numNodes;
}

bool Node::isLeaf() {
    return children.empty();
}

int Node::depthRec(int depth) {
    if (isLeaf())
        return depth;

    int currDepth = depth;
    std::unordered_map<string, Node*>::iterator iter;
    for(iter = children.begin(); iter != children.end(); iter++) {
        Node* child = children.at(iter->first);
        if (child == nullptr) continue;

        int checkDepth = child->depthRec(depth + 1);
        if(checkDepth > currDepth)
            currDepth = checkDepth;
    }

    return currDepth;
}

int Node::getDepth() {
    return depthRec(0);
}
Node *Node::getByLabel(std::string attr, std::string label) {
    Node* parent = this->getByAttr(attr);
    if (parent == nullptr) return nullptr;
    return parent->children.at(label);
}

Node *Node::getByAttr(std::string attribute) {
    if (this->attribute == attribute)
        return this;

    std::unordered_map<string, Node*>::iterator iter;
    for(iter = children.begin(); iter != children.end(); iter++) {
        Node* child = children.at(iter->first);
        if (child->attribute == attribute)
            return child;
        if (!child->isLeaf()) {
            Node* check = child->getByAttr(attribute);
            if (check == nullptr)
                continue;
            if (attribute == check->attribute)
                return check;
        }
    }

    return nullptr;

}

Node *Node::getParent(Node *curr) {
    if (curr == nullptr)
        return nullptr;
    if (curr == this)
        return nullptr;
    if (curr->isLeaf())
        return nullptr;

    std::unordered_map<string, Node*>::iterator iter;
    for(iter = curr->children.begin(); iter != curr->children.end(); iter++) {
        string k =  iter->first;
        Node* n = iter->second;

        Node* currChild = curr->children.at(k);
        if (currChild == nullptr)
            continue;
        if (currChild == this)
            return curr;
        if (!curr->isLeaf()) {
            Node* parent = this->getParent(curr);
            if (parent != nullptr)
                return parent;
        }
    }

    return nullptr;

}

bool Node::hasChild(Node child) {
    return false;
}

void Node::addChild(std::string label, Node *child) {
    if (child == nullptr)
        return ;
    children.insert(make_pair(label, child));
}

bool Node::hasLabel(std::string label) {
    return children.find(label) != children.end();
}

