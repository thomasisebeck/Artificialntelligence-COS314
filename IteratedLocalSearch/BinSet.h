#pragma once
#include "Bin.h"
#include <vector>
#include <string>
#include <queue>

enum fitType {
    FIRST,
    BEST,
    BAD
};

enum searchType {
    ITERATED_LOCAL,
    TABOO
};

class BinSetFirstFit;
class BinSetBestFit;

class BinSet {
private:
    std::vector<Bin*> getCopy();
    std::vector<int> taboo;
    void deleteById(int id);
protected:
    std::vector<Bin*> bins;
    int capacity;
    int currID;
    int getRemainingSpace(int item);
public:
    BinSet(BinSet* old);
    BinSet(int capacity);
    int getCapacity();
    void printBins();
    virtual void addItem(int item) = 0;
    void localSearch();
    void tabooSearch(fitType type);
    int getID();
    void perturb();
    int getBinsUsed();
    virtual ~BinSet();
};