#include "Bin.h"
#include <iostream>
#include <list>
using namespace std;

Bin::Bin(int capacity, int id) {
    this->capacity = capacity;
    this->usedSpace = 0;
    this->id = id;
}

int Bin::getID() {
    return this->id;
}

Bin::Bin(Bin* old) {
    this->capacity = old->capacity;
    this->usedSpace = old->usedSpace;
    this->items = old->items;
}

bool Bin::addItem(int item) {
    if (item + usedSpace > capacity)
        return false;

    usedSpace += item;
    items.push_back(item);

    return true;
}

int Bin::getUsedSpace() {
    this->recaculateUsedSpace();
    return usedSpace;
}


int Bin::getCapacity(){
    return capacity;
}

//int Bin::getRemainingSpace() {
//    return capacity - usedSpace;
//}

void Bin::recaculateUsedSpace() {
    this->usedSpace = 0;
    for (int i : items)
        this->usedSpace += i;
}


//int Bin::removeRandom() {
//    if (this->items.size() == 0)
//        return -1;
//
//    int index = rand() % this->items.size();
//
//    //get to the item and remove it
//    int toRet = *(this->items.erase(items.begin() + index));
//    recaculateUsedSpace();
//    return toRet;
//}

//bool Bin::trySwap(int toAdd, int toRemove) {
//    return (this->usedSpace - toRemove + toAdd) <= capacity;
//}

int Bin::getFreeSpace() {
    recaculateUsedSpace();
    return this->capacity - this->usedSpace;
}

//void Bin::printItems() {
//    for (int i : items)
//        cout << i << " ";
//    cout << endl;
//}

int Bin::removeItem(int toRemove, string binName) {
    vector<int>::iterator it;
    for (it = this->items.begin(); it != this->items.end(); it++) {
        if ((*it) == toRemove) {
            int toRet = *it;
            usedSpace -= toRet;
            this->items.erase(it);
            return toRet;
        }
    }

    cout << endl;

    cout << "Failed to find item " << toRemove << " from " << binName << endl;

    return -1;
}

Bin::~Bin() {}