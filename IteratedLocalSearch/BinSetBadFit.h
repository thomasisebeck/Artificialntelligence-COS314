#pragma once
#include "BinSet.h"
#include <vector>
#include <cstdlib>

class BinSetBadFit: public BinSet {
public:
    BinSetBadFit(int capacity) : BinSet(capacity) {}

    virtual void addItem(int item) {
        int random;
        if (!bins.empty())
            random = rand() % bins.size();
        else {
            bins.push_back(new Bin(this->getCapacity(), this->currID++));
            bins[0]->addItem(item);
            return ;
        }

        if (bins[random]->addItem(item))
            return;

        bins.push_back(new Bin(this->getCapacity(), this->currID++));
        bins[bins.size() - 1]->addItem(item);
    }
};
