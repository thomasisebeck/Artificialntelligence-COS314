#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Network.h"
#include "GP.h"
#include "sharedTypes.h"
using namespace std;

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

            bool discard = false;

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
                discard = true;
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
                discard = true;
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- positive -------------------------//
            currValue = line;

            if (currValue == "no")
                instance.positive = 0;
            else if (currValue == "yes")
                instance.positive = 1;
            else {
                cout << currValue << endl;
                throw "positive not found";
            }

            if (!discard)
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

void NeuralNetwork() {

    vector<dataInstace> instances = getDataInstances();
    shuffle(instances);

    const int EPOCHS = 5;

    try {

        int truePositives = 0;
        int falsePositives = 0;
        int trueNegatives = 0;
        int falseNegatives = 0;

        int zero = 0;
        int one = 0;

        for (int i = 0; i < EPOCHS; i++) {

            vector<int> topology = {9, 5, 4, 1}; //71%
            float alpha = 0.1; //71%
            Network n(topology, alpha);//10050

            //set random, small weights
            setInitialWeights(n,topology);

            for (int trainingCounter = 0; trainingCounter < instances.size(); trainingCounter++) {

                vector<double> inputVals = {
                        instances[trainingCounter].age,
                        instances[trainingCounter].maturity,
                        instances[trainingCounter].maturedBy,
                        instances[trainingCounter].weeks,
                        instances[trainingCounter].size,
                        instances[trainingCounter].side,
                        instances[trainingCounter].specificSide,
                        instances[trainingCounter].isMalig,
                        instances[trainingCounter].positive
                };

                vector<double> targetVals = {instances[trainingCounter].recurrent};

                n.resetErrorTerms();
                n.setInputVals(inputVals);
                n.setTargetVals(targetVals);
                n.feedForward();
                n.storeErrorTerms();
                n.backPropagate();
                n.correctWeights();

                n.print();

            }

            for (int testingCounter = 0; testingCounter < instances.size(); testingCounter++) {
                vector<double> inputVals = {
                        instances[testingCounter].age,
                        instances[testingCounter].maturity,
                        instances[testingCounter].maturedBy,
                        instances[testingCounter].weeks,
                        instances[testingCounter].size,
                        instances[testingCounter].side,
                        instances[testingCounter].specificSide,
                        instances[testingCounter].isMalig,
                        instances[testingCounter].positive
                };

                vector<double> targetVals = {instances[testingCounter].recurrent};

                n.setInputVals(inputVals);
                n.feedForward();
                vector<double> myOutput = n.getOutputValues();

//                cout << myOutput[0] << endl;

//                n.print();

                if (myOutput[0] == targetVals[0]) {
                    if (myOutput[0] == 0) //true negative
                        trueNegatives++;
                    if (myOutput[0] == 1) //true positive
                        truePositives++;
                }
                else {
                    if (myOutput[0] == 1) //false positive
                        falsePositives++;
                    if (myOutput[0] == 0) //false negative
                        falseNegatives++;
                }
            }

        } //epoch counter

//        cout << "Accuracy: " << setprecision(2) << static_cast<double>(truePositives + trueNegatives) / (truePositives + trueNegatives + falsePositives + falseNegatives) * 100 << "%" << endl;

        double recall = static_cast<double>(truePositives) / (truePositives + falseNegatives);
        double precision = static_cast<double>(truePositives) / (truePositives + falsePositives);

//        cout << "TP" << truePositives << endl;
//        cout << "TN" << trueNegatives << endl;
//        cout << "FP" << falsePositives << endl;
//        cout << "FN" << falseNegatives << endl;
//
//        cout << "F-score: " << setprecision(2) << 2 * static_cast<double>(precision * recall) / (precision + recall) << endl;

    } catch (const char * msg) {
        cout << msg << endl;
    }
}

void Genetic() {

    vector<dataInstace> instances = getDataInstances();
    shuffle(instances);

    Tree myTree(5, instances);
    myTree.print();


}

int main() {

   NeuralNetwork();

    try {
        //Genetic();
    } catch (const char* msg) {
        cout << endl << "ERROR: ";
        cout << msg << endl;
    }   catch (int msg) {
        cout << endl << "ERROR: ";
        cout << msg << endl;
    }

    return 0;
}