#pragma once
#include <vector>
#include <random>
#include <ctime>


class RouletteWheel {
    std::vector<int> fitnesses;
    int sum;
public:
    RouletteWheel(std::vector<int> fitnesses) {
        this->fitnesses = fitnesses;

        this->sum = 0;

        std::vector<int>::iterator iter;
        for (iter = fitnesses.begin(); iter != fitnesses.end(); iter++)
            sum += *iter;

        srand(time(NULL));
    }

    int spinAndGetIndex() {
        //random number between 0 and tournament size
        float r = rand() / static_cast<float>(RAND_MAX);
         r *= sum;

         //see where r lies
         for (int i = 0; i < fitnesses.size(); i++) {
             r -= fitnesses[i];
             if (r <= 0)
                 return i;
         }

         return 0;
    }
};