#include <iostream>
#include <vector>
#include <fstream>
#include "Network.h"
#include <cmath>
#include <iomanip>
#include <bitset>

using namespace std;

//no-recurrence-events,30-39,premeno,30-34,0-2,no,3,left,left_low,no

struct dataInstace {
    vector<int> recurrent;
    vector<int> age;
    vector<int> maturity;
    vector<int> maturedBy;
    vector<int> weeks;
    vector<int> isMalig;
    vector<int> size;
    vector<int> side;
    vector<int> specificSide;
    vector<int> positive;
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

    bool discard;

    //read the data instances
    try {

        while (!myFile.eof()) {

            discard = false;

            dataInstace instance;

            //--------------------- recurrent -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "no-recurrence-events")
                instance.recurrent = { 0 };
            else if (currValue == "recurrence-events")
                instance.recurrent = { 1 };
            else {
                cout << "recurrent type: " << currValue << endl;
                throw "recurrent type not found";
            }

            //--------------------- age -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "20-29")
                instance.age = { 0, 0, 0 };
            else if (currValue == "30-39")
                instance.age = { 0, 0, 1 };
            else if (currValue == "40-49")
                instance.age = { 0, 1, 0 };
            else if (currValue == "50-59")
                instance.age = { 0, 1, 1 };
            else if (currValue == "60-69")
                instance.age = { 1, 0, 0 };
            else if (currValue == "70-79")
                instance.age = { 1, 0, 1};
            else {
                cout << "age not found: " << currValue << endl;
                throw "age not found";
            }


            //--------------------- maturity -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "premeno")
                instance.maturity = {0, 0};
            else if (currValue == "ge40")
                instance.maturity = {0, 1};
            else if (currValue == "lt40")
                instance.maturity = {1, 0};
            else
                throw "maturity not found";

            //--------------------- maturedBy -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "0-4")
                instance.maturedBy = { 0, 0, 0, 0};
            else if (currValue == "5-9")
                instance.maturedBy = { 0, 0, 0, 1};
            else if (currValue == "10-14")
                instance.maturedBy = { 0, 0, 1, 0};
            else if (currValue == "15-19")
                instance.maturedBy = { 0, 0, 1, 1};
            else if (currValue == "20-24")
                instance.maturedBy = { 0, 1, 0, 0};
            else if (currValue == "25-29")
                instance.maturedBy = { 0, 1, 0, 1};
            else if (currValue == "30-34")
                instance.maturedBy = { 0, 1, 1, 0};
            else if (currValue == "35-39")
                instance.maturedBy = { 0, 1, 1, 1};
            else if (currValue == "40-44")
                instance.maturedBy = { 1, 0, 0, 0};
            else if (currValue == "45-49")
                instance.maturedBy = { 1, 0, 0, 1};
            else if (currValue == "50-54")
                instance.maturedBy = { 1, 0, 1, 0};
            else {
                cout << currValue << endl;
                throw "matured by not found";
            }

            //--------------------- weeks -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "0-2")
                instance.weeks = { 0, 0, 0, 0 };
            else if (currValue == "3-5")
                instance.weeks = { 0, 0, 0, 1 };
            else if (currValue == "6-8")
                instance.weeks = { 0, 0, 1, 0 };
            else if (currValue == "9-11")
                instance.weeks = { 0, 0, 1, 1 };
            else if (currValue == "12-14")
                instance.weeks = { 0, 1, 0, 0 };
            else if (currValue == "15-17")
                instance.weeks = { 0, 1, 0, 1 };
            else if (currValue == "24-26")
                instance.weeks = { 0, 1, 1, 0 };
            else {
                cout << currValue << endl;
                throw "weeks by not found";
            }

            //--------------------- isMalig -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "yes")
                instance.isMalig = { 0, 0 };
            else if (currValue == "no")
                instance.isMalig = { 0, 1 };
            else if (currValue == "?") {
                discard = true;
                instance.isMalig = {1, 0};
            }
            else {
                cout << currValue << endl;
                throw "is malig by not found";
            }

            //--------------------- size -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "1")
                instance.size = { 0, 0};
            else if (currValue == "2")
                instance.size = {0, 1};
            else if (currValue == "3")
                instance.size = {1, 0};
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- side -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "left")
                instance.side = {0};
            else if (currValue == "right")
                instance.side = {1};
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- specificSide -------------------------//
            currValue = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);

            if (currValue == "left_low")
                instance.specificSide = {0, 0, 0};
            else if (currValue == "left_up")
                instance.specificSide = {0, 0, 1};
            else if (currValue == "right_low")
                instance.specificSide = {0, 1, 0};
            else if (currValue == "right_up")
                instance.specificSide = {0, 1, 1};
            else if (currValue == "central")
                instance.specificSide = {1, 0, 0};
            else if (currValue == "?") {
                discard = true;
                instance.specificSide = {1, 0, 1};
            }
            else {
                cout << currValue << endl;
                throw "size not found";
            }

            //--------------------- specificSide -------------------------//
            currValue = line;

            if (currValue == "no")
                instance.positive = {0};
            else if (currValue == "yes")
                instance.positive = {1};
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

void smallerNetwork() {
        vector<int> topology = {3, 2};

        //change alpha to 0.25
        Network n(topology, 0.5);

        try {

            vector<vector<double>> trainingSetInput = {
                    {0,    1,    1},
                    {0,    0.9,  0.95},
                    {0,    0.75, 0.91},
                    {0.01, 1,    0.85},

                    {1,    0,    1},
                    {0.9,  0,    0.95},
                    {0.95, 0.05, 0.96},
                    {0.98, 0.02, 1}
            };

            vector<vector<double>> trainingSetOutput = {
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 0},

                    {0, 1},
                    {0, 1},
                    {0, 1},
                    {0, 1}
            };

            vector<vector<double>> testSetInput = {
                    {0,    1,    1},
                    {0,    0.9,  0.95},
                    {0,    0.75, 0.91},
                    {0.01, 1,    0.85},

                    {1,    0,    1},
                    {0.9,  0,    0.95},
                    {0.95, 0.05, 0.96},
                    {0.98, 0.02, 1}
            };

            vector<vector<double>> testSetOutput = {
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 0},

                    {0, 1},
                    {0, 1},
                    {0, 1},
                    {0, 1}
            };

            const int EPOCHS = 50;

            for (int i = 0; i < EPOCHS; i++) {

                for (int trainingNumber = 0; trainingNumber < trainingSetInput.size(); trainingNumber++) {
                    n.setInputVals(trainingSetInput[trainingNumber]);
                    n.setTargetVals(trainingSetOutput[trainingNumber]);
                    n.feedForward();
                    n.resetErrorTerms();
                    n.storeErrorTerms();
                    n.backPropagate();
                    n.correctWeights();
                }

            }

            cout << "results: " << endl;

            for (int testNumber = 0; testNumber < testSetInput.size(); testNumber++) {
                n.setInputVals(testSetInput[testNumber]);
                n.setTargetVals(testSetOutput[testNumber]);
                n.feedForward();
                vector<double> outputValues = n.getOutputValues();
                cout << round(testSetInput[testNumber][0]) << " "
                     << round(testSetInput[testNumber][1]) << " "
                     << round(testSetInput[testNumber][2]) << " = "
                     << round(outputValues[0]) << " "
                     << round(outputValues[1]) << endl;
            }
        }
        catch( const char* msg) {
            cout << msg << endl;
        }
};

void largerNetwork() {
    vector<dataInstace> myInstances = readInstances();
    shuffle(myInstances);

    vector<int> topology = {22, 1};
    Network n(topology, 0.25);

    cout << "training..." << endl;

    const int TRAINING_ITERATIONS = 50;

    int total = 0;
    int correct = 0;

    int TP = 0;
    int FP = 0;
    int TN = 0;
    int FN = 0;

    bool converged = false;
    int convergedCounter = 0;
    const int MAX_CONVERGED_ITERS = 500000;

    try {

        for (int i = 0; i < TRAINING_ITERATIONS; i++) {

            if (converged) {
                cout << "Network weights converged" << endl;
                break;
            }

            cout << "iteration " << i << " of " << TRAINING_ITERATIONS << endl;

            for (int outer = 0; outer < myInstances.size() - 6; outer++) {

                for (int loopOver = 0; loopOver < 20; loopOver++) {

                    for (int inner = 0; inner < 5; inner++) {

                        vector<vector<int>> inputVals = {
                                myInstances[outer + inner + (outer % 2)].recurrent,
                                myInstances[outer + inner + (outer % 2)].age,
                                myInstances[outer + inner + (outer % 2)].maturity,
                                myInstances[outer + inner + (outer % 2)].maturedBy,
                                myInstances[outer + inner + (outer % 2)].weeks,
                                myInstances[outer + inner + (outer % 2)].size,
                                myInstances[outer + inner + (outer % 2)].side,
                                myInstances[outer + inner + (outer % 2)].specificSide,
                                myInstances[outer + inner + (outer % 2)].isMalig
                        };

                        //bild the target vals array
                        vector<double> useInputVals;
                        for (int i = 0; i < inputVals.size(); i++)
                            for (int j = 0; j < inputVals[i].size(); j++)
                                useInputVals.push_back(inputVals[i][j]);

                        vector<double> targetVals = {
                                static_cast<double>(myInstances[outer + inner + (outer % 2)].positive[0])
                        };

//                            cout << useInputVals.size() << endl;

                        n.setInputVals(useInputVals);
                        n.setTargetVals(targetVals);
                        n.feedForward();
                        vector<double> outputValues = n.getOutputValues();
                        n.resetErrorTerms();
                        n.storeErrorTerms();
                        n.backPropagate();
                        if (!n.correctWeights()) { //converged
                            convergedCounter++;
                            if (convergedCounter > MAX_CONVERGED_ITERS)
                                converged = true;
                        }


                    }

                }

            }

        }

        //test the accuracy

        for (dataInstace d : myInstances) {
            vector<vector<int>> inputVals = {
                    d.recurrent,
                    d.age,
                    d.maturity,
                    d.maturedBy,
                    d.weeks,
                    d.size,
                    d.side,
                    d.specificSide,
                    d.isMalig
            };

            //bild the target vals array
            vector<double> useInputVals;
            for (int i = 0; i < inputVals.size(); i++)
                for (int j = 0; j < inputVals[i].size(); j++)
                    useInputVals.push_back(inputVals[i][j]);

            vector<double> targetVals = {
                    static_cast<double>(d.positive[0])
            };

            n.setInputVals(useInputVals);
            n.setTargetVals(targetVals);
            n.feedForward();
            vector<double> outputValues = n.getOutputValues();

            cout << "network got: " << round(outputValues[0]) << ", should be: " << d.positive[0] << endl;
            if (round(outputValues[0]) == d.positive[0]) {
                correct++;
                //increase true counter
                if (d.positive[0] == 1)
                    TP++;
                else
                    TN++;
            } else {
                //increase false counter
                if (d.positive[0] == 1)
                    FP++;
                else
                    FN++;
            }
            total++;
        }




    } catch (const char* msg) {
        cout << msg << endl;
    }



    cout << "accuracy: " << setprecision(2) << static_cast<double>(correct) / total  * 100 << "%" << endl;
    double precision = static_cast<double>(TP) / (TP + FP);
    double recall = static_cast<double>(TP) / (TP + FN);
    cout << "f-measure: " << setprecision(2) << static_cast<double>(2 * precision * recall) / (precision + recall);
}

int main() {

    largerNetwork();

    return 0;
}