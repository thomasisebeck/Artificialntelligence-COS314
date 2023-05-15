#pragma once
#include "sharedTypes.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class ACO {
    //2d array of items to connect
    std::vector<Item> items;
    std::vector<int> indices;
    float totalWeight;
    float pheremonesToDeposit;
    float bestValue;
    string bestSolution;

    int getNextItem(vector<int> visitedItems) {
        vector<int> canVisit;

        //make a list of the unvisited items
        for (int i = 0; i < items.size(); i++)
            if (std::find(visitedItems.begin(), visitedItems.end(), i) == visitedItems.end())
                canVisit.push_back(i);

        //get the sum of the pheremones on the items
        float sumPheremones = 0;
        for (int i : canVisit)
            sumPheremones += items[i].pheremoneLevel;

        //random number between 0 and pheremone level
        float randomNumber = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/sumPheremones));


        //subtract until you choose the next item
        for (int i : canVisit) {
            randomNumber -= items[i].pheremoneLevel;
            if (randomNumber <= 0)
                return i;
        }

        throw "Indices not calcuated correctly!";

    }

public:

    ACO(std::vector<Item> items, float totalWeight, float pheremonesToDeposit) {
        this->items = items;
        this->totalWeight = totalWeight;
        this->pheremonesToDeposit = pheremonesToDeposit;
        this->bestValue = 0;

        srand (static_cast <unsigned> (time(0)));
        bestSolution = "no solution found";
    }

    float getValue() {
        return bestValue;
    }


    string getBestSolution() {
        return bestSolution;
    }

    void travelRoute() {
        //get a random starting point
        int itemStart = rand() % items.size();
        vector<int> visitedItems;
        visitedItems.push_back(itemStart);

        float totWeight = items[itemStart].weight;
        float totValue = items[itemStart].value;

        //travel the route and keep track of visited items
        while (visitedItems.size() != items.size()) {
            int nextItemIndex = getNextItem(visitedItems);

            totWeight += items[nextItemIndex].weight;
            if (totWeight > totalWeight)
                break;

            totValue += items[nextItemIndex].value;

            //valid to visit, does not exceed weight
            visitedItems.push_back(nextItemIndex);
        }

        float currValue = 0;
        //get the value
        for (int i = 0; i < visitedItems.size(); i++)
            currValue += items[visitedItems[i]].value;

        if (currValue > bestValue) { //store this instance
            bestValue = currValue;
            bestSolution = "";
            for (int i = 0; i < items.size(); i++)
                bestSolution += "0";

            for (int i: visitedItems)
                bestSolution[i] = '1';

            stringstream strm;
            strm << std::fixed << std::setprecision(0) << bestValue;

            bestSolution += "(" + strm.str() + ")";
        }

        //deposit pheromones proportional to value
        for (int i : visitedItems)
            items[i].pheremoneLevel += pheremonesToDeposit * totValue;

    }

    void printItems() {
        for (Item i : items)
            cout << i.pheremoneLevel << " ";
        cout << endl;
    }

    float getBestFitness() {
        return bestValue;
    }
};
