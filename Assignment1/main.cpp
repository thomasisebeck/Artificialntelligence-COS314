#include <iostream>
#include "BinSetFirstFit.h"
#include "BinSetBestFit.h"
#include "BinSetBadFit.h"
#include "DataSet.h"
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

//read file and get vector
vector<int> readFile(const string filePath, int& containerSize) {
    fstream myFile;
    string path = filePath;
    myFile.open(path);
    if (!myFile) {
        cout << "failed to open file" << endl;
        cout << "path: " << path << endl;
    }

    string line;

    //skip first line (line numbers)
    getline(myFile, line);

    //container size
    getline(myFile, line);
    containerSize = stoi(line);

    vector<int> myVector;
    //add all nodes to the vector
    while (getline(myFile, line))
        myVector.push_back(stoi(line));


    myFile.close();

    return myVector;
}

string extractName(string line) {
    while (line.find("\\") != std::string::npos) {
        line = line.substr(line.find("\\") + 1, line.length());
    }
    return line.substr(0, line.find(".txt"));
}

string getSetFromPath(string filePath) {
    string set = "not found";

    if (filePath.find("Falkenauer_T") != std::string::npos)
        set = "Falkenauer_T";
    if (filePath.find("Falkenauer_U") != std::string::npos)
        set = "Falkenauer_U";
    if (filePath.find("Hard28") != std::string::npos)
        set = "Hard28";
    if (filePath.find("Scholl_1") != std::string::npos)
        set = "Scholl_1";
    if (filePath.find("Scholl_2") != std::string::npos)
        set = "Scholl_2";
    if (filePath.find("Scholl_3") != std::string::npos)
        set = "Scholl_3";
    if (filePath.find("Schwerin_1") != std::string::npos)
        set = "Schwerin_1";
    if (filePath.find("Schwerin_2") != std::string::npos)
        set = "Schwerin_2";
    if (filePath.find("Waescher") != std::string::npos)
        set = "Waescher";

    return set;
}

void addToSet(DataSet& dataSet, string filePath, int solution, int optimum, searchType stype, bool isRunTime = false, double runtime = 0) {

    string set = getSetFromPath(filePath);

    if (!isRunTime)
        dataSet.add(solution, optimum, set, stype);
    else
        dataSet.addRunTime(set, runtime, stype);

}

void testFile(string filePath, int optimum, fitType ftype, searchType stype, DataSet& data) {

    vector<string> problemInstances;

    int containerSize;
    //ordered vector
    vector<int> myVector = readFile(filePath, containerSize);

    //create a binset
    BinSet* myBinSet = nullptr;

    switch (ftype) {
        case FIRST:
            myBinSet = new BinSetFirstFit(containerSize);
            break;
        case BEST:
            myBinSet = new BinSetBestFit(containerSize);
            break;
        case BAD:
            myBinSet = new BinSetBadFit(containerSize);
    }

    //add to binset in loop (pop front)
    for (int i : myVector) {
        myBinSet->addItem(i);
    }

    myVector.clear();

    int solution = 1000000;

    const int ITERATIONS_LOCAL = 80; //don't go over 80
    const int ITERATIONS_TABOO = ITERATIONS_LOCAL / 8; //adjust for extra time complexity of taboo

    string filename;

    switch (stype) {
        case ITERATED_LOCAL:
            for (int i = 0; i < ITERATIONS_LOCAL; i++) {
                myBinSet->localSearch(); //peform the local search
                if (myBinSet->getBinsUsed() < solution) { //test if you got a better result
                    solution = myBinSet->getBinsUsed();
                }
            }

            addToSet(data, filePath, solution, optimum, stype);
            break;

        case TABOO:
            for (int i = 0; i < ITERATIONS_TABOO; i++) {
                myBinSet->tabooSearch(ftype);
                if (myBinSet->getBinsUsed() < solution) { //test if you got a better result
                    solution = myBinSet->getBinsUsed();
                }
            }

            addToSet(data, filePath, solution, optimum, stype);

    }

    delete myBinSet;

}

struct file {
    string fileName;
    string filePath;
    int optimum;
};

int getOptimum(string filename) {
    //read optimum.txt
    string line;
    ifstream file;
    file.open("optima.txt");

    //remove the .txt

    filename = filename.substr(0, filename.find(".txt"));

    while (getline(file, line)) {
        if (line.find(filename) != std::string::npos) {
            line.erase(0, line.find(' '));
            return stoi(line);
        }
    }

    file.close();

    return -1;
}

int main() {
    //read the list

    string line;
    ifstream myFile;
    myFile.open("list.txt");

    if (!myFile)
        cout << "Failed to open list.txt" << endl;

    vector<file> fileArray;

    while (getline(myFile, line)) {
        string filename = extractName(line);
        int opt = getOptimum(filename);

        struct file fileStruct;

        fileStruct.fileName = filename;
        fileStruct.optimum = opt;
        fileStruct.filePath = line;

        //push to the vector...
        fileArray.push_back(fileStruct);
    }

    myFile.close();

    //make a vector to store optimums and file paths
    DataSet dataSet;

    double tabooTime = 0;
    double ILSTime = 0;

    int i = 0;
    for (file f : fileArray) {
        cout << setprecision(2) << "testing: \t" << f.fileName << " (" << static_cast<double>(i++)/fileArray.size() * 100 << "%)" << endl;

        //------------------------ test ILS --------------------------//

        auto start1 = std::chrono::steady_clock::now();

        //test the file
        testFile(f.filePath, f.optimum, BAD, ITERATED_LOCAL, dataSet);

        auto end1 = std::chrono::steady_clock::now();
        auto diff = end1 - start1;
        ILSTime = std::chrono::duration<double, std::milli> (diff).count() / 1000;
        dataSet.addRunTime(getSetFromPath(f.filePath), ILSTime, ITERATED_LOCAL);

        //----------------------- test Taboo -------------------------//

        start1 = std::chrono::steady_clock::now();

        //test the file
        testFile(f.filePath, f.optimum, BAD, TABOO, dataSet);

        end1 = std::chrono::steady_clock::now();
        diff = end1 - start1;
        tabooTime = std::chrono::duration<double, std::milli> (diff).count() / 1000;
        dataSet.addRunTime(getSetFromPath(f.filePath), tabooTime, TABOO);
    }

    dataSet.getResult();
    dataSet.getRunTimes();

    return 0;
}