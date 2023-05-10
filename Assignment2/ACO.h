#pragma once
#include "sharedTypes.h"
#include <string>
#include <algorithm>

//all edges are connected!
//only thing you have to account for is the pheremone level
struct Edge {
    float pheromoneLevel;
};

class ACO {
    //2d array of items to connect
    std::vector< std::vector<Edge> > edges;
    std::vector<Item> items;
    std::vector<int> indices;

    //eg: edge[0][1], is between item 0 and 1

    ACO(int numberOfItems, std::vector<Item> items) {

        Edge e;
        e.pheromoneLevel = 1;

        //initialise the vector (2d array of connections)
        for (int i = 0; i < numberOfItems; i++)
            for (int j = 0; j < numberOfItems; j++) {
                edges[i][j] = e;
            }

        this->items = items;

        for (int i = 0; i < items.size(); i++)
            indices.push_back(i);

        srand (static_cast <unsigned> (time(0)));
    }

    int getItemIndex(Item i, std::vector<Item> items) {
        int index = 0;
        std::vector<Item>::iterator iter;
        for (iter = items.begin(); iter != items.end(); iter++, index++)
            if (iter->value == i.value && iter->weight == i.weight)
                return index;
        return -1;
    }

    int getNextItemToVisit(Item i, vector<int> visitedItems) {
        //get sum of pheromones on the edges
        int index = getItemIndex(i, this->items);
        vector<Edge> possibleEdges;

        //get the sum of the pheromone levels and push the possible edges
        int sum = 0;
        for (Edge e : edges[index]) {
            auto it = std::find(visitedItems.begin(), visitedItems.end(), index);
            if (it == visitedItems.end()) { //not visited, possible to visit
                sum += e.pheromoneLevel;
                possibleEdges.push_back(e);
            }
        }

        //random number from 0 to sum
        float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/sum);

        //subtract until you choose the edge
        for (Edge e: possibleEdges) {
            randomNumber -= e.pheromoneLevel;
            if (randomNumber <= 0)
                return e;
        }

        throw "Could not find edge!";
    }

    int getEdgeIndex(Edge e) {
        std::vector< std::vector<Edge> >::iterator iter;
        for (int i = 0; i < edges.size(); i++)
            if (i == )
    }


    void travelRoute() {
        //get a random starting point
        int itemStart = rand() % items.size();
        vector<int> visitedItems;
        visitedItems.push_back(itemStart);

        //travel the route and keep track of visited items


        //if the route is valid, deposit on


    }


};
