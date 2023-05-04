#include <iostream>
#include <fstream>
#include <vector>
#include "sharedTypes.h"
using namespace std;

void testInstance(problemInstance instance) {
    cout << "Testing instance" << endl;
    cout << "Items: " << endl;
}

struct fileType {
    string filename;
    double optimum;
};

int main() {

    vector<fileType> fileVector {
            { "Instances/f1_l-d_kp_10_269", 295},
            { "Instances/f2_l-d_kp_20_878", 1024},
            { "Instances/f3_l-d_kp_4_20", 35},
            { "Instances/f4_l-d_kp_4_11", 23},
            { "Instances/f5_l-d_kp_15_375", 481.0694},
            { "Instances/f6_l-d_kp_10_60", 52},
            { "Instances/f7_l-d_kp_7_50", 107},
            { "Instances/knapPI_1_100_1000_1", 9147},
            { "Instances/f8_l-d_kp_23_10000", 9767},
            { "Instances/f9_l-d_kp_5_80", 130},
            { "Instances/f10_l-d_kp_20_879", 1025},
    };

    vector<problemInstance> instances;
    vector<int> items;

    for (fileType file: fileVector) {
        //clear vector
        items.clear();

        ifstream myFile(file.filename);

        //init the name and optimum
        problemInstance instance;
        instance.name = file.filename;
        instance.optimum = file.optimum;

        string line;

        //get first line: <no lines> <capacity>
        getline(myFile, line);

        //load the values into the vector
        while (getline(myFile, line)) {
            Item newItem;
            newItem.weight = stoi(line.substr(0, line.find(' ')));
            line.erase(line.find(' ') + 1);
            newItem.value = stoi(line);
            instance.items.push_back(newItem);
        }

        myFile.close();

        //test

    }

    return 0;

}