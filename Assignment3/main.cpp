#include <iostream>
#include <vector>
#include <fstream>
#include "Network.h"
#include <cmath>
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

/*
 Network n({2, 3, 1}, 0.1);

    n.connections[0].setWeight(0,0,0.11);
    n.connections[0].setWeight(1,0,0.21);
    n.connections[0].setWeight(0,1,0.12);
    n.connections[0].setWeight(1,1,0.08);

    n.connections[1].setWeight(1,0, 0.14);
    n.connections[1].setWeight(0,0, 0.15);

    try {

        n.setInputVals({2, 3});
        n.setTargetVals({1});

        for (int i = 0; i < 200; i++) {

            n.feedForward();
            vector<double> outputValues = n.getOutputValues();
            n.resetErrorTerms();
            n.storeErrorTerms();
            n.backPropagate();
            n.correctWeights();
            n.printOutputError();


        }

    } catch (const char* msg) {
        cout << msg << endl;
    }
 */

vector<dataInstace> readInstances() {
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

int main() {

    vector<dataInstace> myInstances = readInstances();

    try {

        vector<int> topology = {2, 1};
        Network n(topology, 0.25);
        vector<double> targetVals = {0};
        vector<double> inputVals = {0, 1};
        n.setInputVals(inputVals);
        n.setTargetVals(targetVals);

        n.connections[0].setWeight(0, 0, 1);
        n.connections[0].setWeight(0, 1, 1);
        n.connections[0].setWeight(0, 1, 1);
        n.connections[0].biasWeights = {0};
//
//        n.feedForward();
//        vector<double> outputValues = n.getOutputValues();
//        cout << outputValues[0] << endl;

        for (int i = 0; i < 2000; i++) {

            n.feedForward();
            vector<double> outputValues = n.getOutputValues();
            cout << outputValues[0] << endl;
            n.resetErrorTerms();
            n.storeErrorTerms();
            n.backPropagate();
            n.correctWeights();
            n.print();
        }



/*
        for (dataInstace d : myInstances) {

//            vector<double> inputVals = {
//                    d.age,
//                    d.maturity,
//                    d.maturedBy,
//                    d.weeks,
//                    d.size,
//                    d.side,
//                    d.specificSide
//            };
//            vector<double> targetVals = { d.isMalig };

            vector<double> inputVals = { 1, 0 };
            n.setInputVals(inputVals);
            vector<double> targetVals = { 1 };
            n.setTargetVals(targetVals);
            n.feedForward();
            vector<double> outputValues = n.getOutputValues();
            n.resetErrorTerms();
            n.storeErrorTerms();
            n.backPropagate();
            n.correctWeights();

            cout << "for 1 0 , got " << outputValues[0] << endl;



            cout << "for 0 1 , got " << outputValues[0] << endl;



        }
*/
    } catch (const char* msg) {
        cout << msg << endl;
    }

    return 0;
}