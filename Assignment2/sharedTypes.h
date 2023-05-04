#pragma once
#include <vector>
using namespace std;

struct Item {
    int weight;
    int value;
};

struct problemInstance {
    vector<Item> items;
    int optimum;
    string name;
};