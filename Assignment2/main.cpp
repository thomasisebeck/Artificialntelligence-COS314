#include <iostream>
#include <fstream>
#include <vector>
#include "sharedTypes.h"
using namespace std;

void testFile(string filename) {

}

struct fileType {
    string filename;
    double optimum;
};

int main() {

    vector<fileType> fileVector {
            { "Instances/f1_l-d_kp_10_269.txt", 295},
            { "Instances/f2_l-d_kp_20_878.txt", 1024},
            { "Instances/f3_l-d_kp_4_20.txt", 35},
            { "Instances/f4_l-d_kp_4_11.txt", 23},
            { "Instances/f5_l-d_kp_15_375.txt", 481.0694},
            { "Instances/f6_l-d_kp_10_60.txt", 52},
            { "Instances/f7_l-d_kp_7_50.txt", 107},
            { "Instances/knapPI_1_100_1000_1.txt", 9147},
            { "Instances/f8_l-d_kp_23_10000.txt", 9767},
            { "Instances/f9_l-d_kp_5_80.txt", 130},
            { "Instances/f10_l-d_kp_20_879.txt", 1025},
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

        string line;
        //load the values into the vector
        while (getline(myFile, line)) {
            Item newItem;
            newItem.weight = stoi(line.substr(0, line.find(' ')));
            line.erase(line.find((' ') + 1));
            newItem.value = stoi(line);
            instance.items.push_back(newItem);
        }

        myFile.close();

        //test
    }

    return 0;

}