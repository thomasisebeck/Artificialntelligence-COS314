#include "BinSet.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

BinSet::BinSet(int capacity) {
    this->capacity = capacity;
    this->currID = 0;
}

int BinSet::getCapacity() {
    return capacity;
}

vector<Bin*> BinSet::getCopy() {
    vector<Bin*> newBinset;

    for (Bin* bin : this->bins)
        newBinset.push_back(new Bin(bin));

    return newBinset;
}

int BinSet::getBinsUsed() {
    return bins.size();
}


void BinSet::printBins() {
    cout << "----- Bins -----" << endl;
    cout << "Number of bins: " << bins.size() << endl;
    vector<Bin*>::iterator iter;
    for (iter = bins.begin(); iter != bins.end(); iter++)
        cout << (*iter)->getUsedSpace() << "/" << (*iter)->getCapacity() << endl;
    cout << "----------------" << endl;
}

int findItem(vector<int> items, int toFind) {
    for (int i = 0; i < items.size(); i++)
        if (items[i] == toFind)
            return i;

    return -1;
};

bool tryToSwap(Bin* bin1, Bin* bin2, int item1, int item2) {

    int b1Used = bin1->getUsedSpace() - item1 + item2;
    int b2Used = bin2->getUsedSpace() - item2 + item1;

    if (b1Used > bin1->getCapacity())
        return false;
    if (b2Used > bin2->getCapacity())
        return false;

    return true;
}

void BinSet::deleteById(int id) {
    for (int i = 0; i < bins.size(); i++)
        if (bins[i]->getID() == id) {
            auto it = bins.begin();
            std::advance(it, i);
            bins.erase(it);
            return ;
        }

}

/*
 * Based on a modified version of the best point found
 * Each iteration tries to pack items from the least filled bin into all other bins
 * If the least filled bin becomes empty, it is deleted and a new best point is set
 */

BinSet::BinSet(BinSet *old) {

    for (Bin* bin: this->bins)
        delete bin;

    old->taboo.clear();

    for (Bin* bin : old->bins)
       bins.push_back(new Bin(bin));
}

void BinSet::perturb() {

    //unpack half the items into new bins
    vector<Bin*> otherBins;
    vector<Bin*>::iterator iter;
    vector<int>::iterator itemIter;
    vector<Bin*> newBins;

    for (iter = bins.begin(); iter != bins.end(); iter++) {

        //create the other bin to add to the list
        Bin* newBin = new Bin(this->capacity, this->currID++);

        int numLoops = (*iter)->items.size() / 2;


        for (itemIter = (*iter)->items.begin(); itemIter != (*iter)->items.end(); itemIter++) {
            newBin->items.push_back(*itemIter);
            newBin->recaculateUsedSpace();

            numLoops--;
            if (numLoops == 0)
                break;
        }

        newBins.push_back(newBin);
    }

    //push the new bins onto the list
    for (iter = newBins.begin(); iter != newBins.end(); iter++)
        this->bins.push_back(*iter);

    newBins.clear();

}

void BinSet::tabooSearch(fitType type) {

    //do 20 local searches
    for (int i = 0; i < 8; i++)
        this->localSearch();

    int MAX_TABOO_LIST_SIZE = 15;

    vector<int>::iterator iter;
    //see if state is in taboo list
    //loop through the taboo list
    for (iter = taboo.begin(); iter != taboo.end(); iter++)
        if ((*iter) == this->bins.size()) {

            //perturb only 50% of the time...
            if (rand() % 100 > 20)
                perturb(); //got to a taboo state, go somewhere else...

            return ;
        }

    //not in list, push to the list
    taboo.push_back(this->bins.size());

    //delete if the taboo list is too long...
    if (taboo.size() > MAX_TABOO_LIST_SIZE)
        taboo.erase(taboo.begin());
}

void BinSet::localSearch() {

    //get least filled bin
    //try and swap those items with larger items in other bins
    int mostFreeSpace = bins[0]->getFreeSpace();
    Bin* leastFilled = bins[0];

    for (Bin* bin : bins)
        if (bin->getFreeSpace() > mostFreeSpace)
            leastFilled = bin;

    bool mustContinue = false;
    //loop through least filled items
    for (int leastItemInd = 0; leastItemInd < leastFilled->items.size(); leastItemInd++) {
        if (leastFilled->items.empty()) break ; //finished loop

        if (mustContinue)
            mustContinue = false;

        for (Bin* testBin : bins) {
            if (mustContinue)
                continue;
            if (testBin->getID() != leastFilled->getID()) {
                //first see if you can pack into another bin without swapping...

                if (testBin->addItem(leastFilled->items[leastItemInd])) {
                    leastFilled->removeItem(leastFilled->items[leastItemInd], "least initial");
                    mustContinue = true;
                    continue;
                }

                //see if you can swap with the other bin

                //loop through the testbin items
                for (int testItemInd = 0; testItemInd < testBin->items.size(); testItemInd++) {
                    int leastItem = leastFilled->items[leastItemInd];
                    int testItem = testBin->items[testItemInd];

                    if (testItem < leastItem)  //least filled bin item is larger, try swap
                        if (tryToSwap(testBin, leastFilled, testItem, leastItem)) {

                            //peform the swap...
                            int swapTest = testBin->removeItem(testItem, "test inner");
                            int swapLeast = leastFilled->removeItem(leastItem, "least inner");

                            testBin->addItem(swapLeast);
                            leastFilled->addItem(swapTest);

                            testItemInd = 0;
                            leastItemInd = 0;

                            mustContinue = true;
                        }

                    if (mustContinue)
                        continue;

                }
            }
        }
    }

    //modify to become better...
    if (leastFilled->getFreeSpace() == leastFilled->getCapacity())
        this->deleteById(leastFilled->getID());

}

BinSet::~BinSet(){
    vector<Bin*>::iterator iter;
    for (iter = bins.begin(); iter != bins.end(); iter++)
        delete (*iter);
}