#pragma once
#include <vector>
#include <string>

using namespace std;

struct Item {
    float weight;
    float value;
    float pheremoneLevel;
};

enum testType {
    GENETIC,
    ANT
};

struct problemInstance {
    vector<Item> items;
    int optimum;
    string name;
    int capacity;
};