#pragma once
#include "BinSet.h"
#include <vector>
#include <iostream>

class BinSetBestFit: public BinSet {
public:
    BinSetBestFit(int capacity) : BinSet(capacity) {}

    virtual void addItem(int item) {
        int lowestUnusedSpace = this->capacity;
        Bin* bestChoice = nullptr;
        std::vector<Bin*>::iterator iter;

        for (iter = bins.begin(); iter != bins.end(); iter++){
            int currRemainingSpace = ((*iter)->getCapacity() - (*iter)->getUsedSpace()) - item;
            if (currRemainingSpace >= 0) { //fits in bin

                // not yet found a good that fits, or found a better bin
                if (bestChoice == nullptr || currRemainingSpace < lowestUnusedSpace) {
                    bestChoice = (*iter);
                    lowestUnusedSpace = currRemainingSpace;
                }
            }
        }

        if (bestChoice == nullptr) { //bin not found
            Bin* newBin = new Bin(this->capacity, this->currID++);
            newBin->addItem(item);
            bins.push_back(newBin);
            return ;
        }

        //add to best choice bin
        bestChoice->addItem(item);
    }

};