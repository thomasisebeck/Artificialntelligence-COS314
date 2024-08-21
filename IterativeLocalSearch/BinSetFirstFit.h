#pragma once
#include "BinSet.h"
#include <vector>

class BinSetFirstFit: public BinSet {
public:
    BinSetFirstFit(int capacity) : BinSet(capacity) {}

    virtual void addItem(int item) {
        std::vector<Bin*>::iterator iter;
        for (iter = bins.begin(); iter != bins.end(); iter++)
            if ((*iter)->addItem(item))
                return ;

        //failed to add to all bins
        //add a new bin at the end and add the item
        Bin* newBin = new Bin(this->capacity, this->currID++);
        newBin->addItem(item);
        bins.push_back(newBin);
    }
};
