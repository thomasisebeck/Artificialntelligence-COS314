#pragma once
#include "sharedTypes.h"
#include <string>

//all edges are connected!
//only thing you have to account for is the pheremone level
struct Edge {
    float pheromoneLevel;
};

class ACO {
    //2d array of items to connect
    std::vector< std::vector<Edge> > edges;

    //eg: edge[0][1], is between item 0 and 1

    ACO(int numberOfItems) {

        Edge e;
        e.pheromoneLevel = 0;

        //initialise the vector (2d array of connections)
        for (int i = 0; i < numberOfItems; i++)
            for (int j = 0; j < numberOfItems; j++) {
                edges[i][j] = e;
            }

    }


};
