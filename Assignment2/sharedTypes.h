#pragma once
#include <vector>
#include <string>

using namespace std;

struct Item {
    int weight;
    int value;
};

enum testType {
    GENETIC,
    ACO
};

struct problemInstance {
    vector<Item> items;
    int optimum;
    string name;
    int capacity;
};