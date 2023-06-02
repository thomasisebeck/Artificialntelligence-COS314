#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Network.h"
using namespace std;

//no-recurrence-events,30-39,premeno,30-34,0-2,no,3,left,left_low,no

struct dataInstace {
    double recurrent;
    double age;
    double maturity;
    double maturedBy;
    double weeks;
    double isMalig;
    double size;
    double side;
    double specificSide;
    double positive;
};

void shuffle(vector<dataInstace>& array) {
    for (int i = 0; i < array.size(); i++) {
        int index1 = rand() % array.size();
        int index2 = rand() % array.size();
        dataInstace temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }
}

vector<dataInstace> getDataInstances() {

    ifstream myFile;
    myFile.open("data.txt");

    string line;
    string currValue;
    getline(myFile, line);

    vector<dataInstace> instances;

    //read the data instances
    try {

        while (!myFile.eof()) {

            dataInstace instance;

            //--------------------- recurrent -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "no-recurrence-events")
                instance.recurrent = 0;
            else if (currValue == "recurrence-events")
                instance.recurrent = 1;
            else {
                cout << "recurrent type: " << currValue << endl;
                throw "recurrent type not found";
            }

            //--------------------- age -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "20-29")
                instance.age = 0;
            else if (currValue == "30-39")
                instance.age = 1;
            else if (currValue == "40-49")
                instance.age = 2;
            else if (currValue == "50-59")
                instance.age = 3;
            else if (currValue == "60-69")
                instance.age = 4;
            else if (currValue == "70-79")
                instance.age = 5;
            else {
                cout << "age not found: " << currValue << endl;
                throw "age not found";
            }


            //--------------------- maturity -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "premeno")
                instance.maturity = 0;
            else if (currValue == "ge40")
                instance.maturity = 1;
            else if (currValue == "lt40")
                instance.maturity = 2;
            else
                throw "maturity not found";

            //--------------------- maturedBy -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "0-4")
                instance.maturedBy = 0;
            else if (currValue == "5-9")
                instance.maturedBy = 1;
            else if (currValue == "10-14")
                instance.maturedBy = 2;
            else if (currValue == "15-19")
                instance.maturedBy = 3;
            else if (currValue == "20-24")
                instance.maturedBy = 4;
            else if (currValue == "25-29")
                instance.maturedBy = 5;
            else if (currValue == "30-34")
                instance.maturedBy = 6;
            else if (currValue == "35-39")
                instance.maturedBy = 7;
            else if (currValue == "40-44")
                instance.maturedBy = 8;
            else if (currValue == "45-49")
                instance.maturedBy = 9;
            else if (currValue == "50-54")
                instance.maturedBy = 10;
            else {
                cout << currValue << endl;
                throw "matured by not found";
            }

            //--------------------- weeks -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "0-2")
                instance.weeks = 0;
            else if (currValue == "3-5")
                instance.weeks = 1;
            else if (currValue == "6-8")
                instance.weeks = 2;
            else if (currValue == "9-11")
                instance.weeks = 3;
            else if (currValue == "12-14")
                instance.weeks = 4;
            else if (currValue == "15-17")
                instance.weeks = 5;
            else if (currValue == "24-26")
                instance.weeks = 6;
            else {
                cout << currValue << endl;
                throw "weeks by not found";
            }

            //--------------------- isMalig -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "yes")
                instance.isMalig = 0;
            else if (currValue == "no")
                instance.isMalig = 1;
            else if (currValue == "?")
                instance.isMalig = 2;
            else {
                cout << currValue << endl;
                throw "is malig by not found";
            }

            //--------------------- size -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "1")
                instance.size = 0;
            else if (currValue == "2")
                instance.size = 1;
            else if (currValue == "3")
                instance.size = 2;
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- side -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "left")
                instance.side = 0;
            else if (currValue == "right")
                instance.side = 1;
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- specificSide -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "left_low")
                instance.specificSide = 0;
            else if (currValue == "left_up")
                instance.specificSide = 1;
            else if (currValue == "right_low")
                instance.specificSide = 2;
            else if (currValue == "right_up")
                instance.specificSide = 3;
            else if (currValue == "central")
                instance.specificSide = 4;
            else if (currValue == "?")
                instance.specificSide = 5;
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- specificSide -------------------------//
            currValue = line;

            if (currValue == "no")
                instance.positive = 0;
            else if (currValue == "yes")
                instance.positive = 1;
            else {
                cout << currValue << endl;
                throw "positive not found";
            }

            instances.push_back(instance);

            getline(myFile, line);

        }

    } catch (const char* err) {
        cout << err << endl;
    }

    return instances;

}

void setInitialWeights(Network& n, vector<int> topology) {
    for (int layer = 0; layer < topology.size() - 1; layer++)
        for (int row = 0; row < topology[layer]; row++)
            for (int col = 0; col < topology[layer + 1]; col++)
                //set a random, small weight (between 0.1 and 0.5)
                n.connections[layer].setWeight(row, col, static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/0.4) + 0.1));

}

int main() {

    vector<dataInstace> instances = getDataInstances();
    shuffle(instances);

    try {
        //you need 8 input nodes and 1 output node

        vector<int> topology = {9, 5, 10, 1};
        Network n(topology, 0.05);

        //set random, small weights
        setInitialWeights(n,topology);

        cout << "training network..." << endl;

        for (dataInstace d: instances) {

            vector<double> inputVals = {
                    d.age,
                    d.maturity,
                    d.maturedBy,
                    d.weeks,
                    d.size,
                    d.side,
                    d.specificSide,
                    d.isMalig,
                    d.positive
            };

            vector<double> targetVals = { d.recurrent };

            n.resetErrorTerms();
            n.setInputVals(inputVals);
            n.setTargetVals(targetVals);
            n.feedForward();
            n.storeErrorTerms();
            n.backPropagate();
            n.correctWeights();

        }

        cout << "Testing the network..." << endl;

        int correctValues = 0;

        for (dataInstace d: instances) {
            vector<double> inputVals = {
                    d.age,
                    d.maturity,
                    d.maturedBy,
                    d.weeks,
                    d.size,
                    d.side,
                    d.specificSide,
                    d.isMalig,
                    d.positive
            };

            vector<double> targetVals = { d.recurrent };

            n.setInputVals(inputVals);
            n.feedForward();
            vector<double> myOutput = n.getOutputValues();

            if (myOutput[0] == targetVals[0])
                correctValues++;
        }

        cout << "------------- RESULTS ------------" << endl;

        cout << setprecision(2) << (static_cast<double>(correctValues) / instances.size()) * 100 << "%" << endl;

    } catch (const char * msg) {
        cout << msg << endl;
    }

    return 0;
}