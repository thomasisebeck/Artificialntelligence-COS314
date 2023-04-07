#pragma once
#include <vector>
#include <string>

class Bin {
    friend class BinSet;
protected:
    int capacity;
    int usedSpace;
    int id;
    std::vector<int> items;
    void recaculateUsedSpace();
public:
    Bin(int capacity, int id);
    Bin(Bin* old);
    int getID();
    bool addItem(int item);
    int getCapacity();
    int getFreeSpace();
    ~Bin();
    int getUsedSpace();
    int removeItem(int toRemove, std::string binName);
};
