#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct column {
    std::string problemSet;

    int numAtOptimumILS;
    int numNearOptimumILS;
    int sumILS;

    int numAtOptimumTabu;
    int numNearOptimumTabu;
    int sumTabu;
};

struct runtime {
    std::string problemSet;
    double runtime;
    searchType searchType;
};

struct runtimeResult {
    std::string problemSet;
    double ILSRuntime;
    double TabooRuntime;
};

class DataSet {
private:
    std::vector<column> columns;
    std::vector<runtime> runtimes;
public:
    DataSet(){}

    void add(int solution, int optimum, std::string problemSet, searchType type) {

        //add the column
        std::vector<column>::iterator iter;

        bool found = false;

        for (iter = columns.begin(); iter != columns.end(); iter++) {
            if ((*iter).problemSet == problemSet) {
                found = true;
                break;
            }
        }

        if (!found) {
            columns.push_back({problemSet, 0, 0, 0, 0, 0, 0});
            iter = columns.begin();
        }

        if (solution == optimum) {
            if (type == ITERATED_LOCAL) {
                (*iter).numAtOptimumILS++;
                (*iter).sumILS++;
            }
            else { //tabu
                (*iter).numAtOptimumTabu++;
                (*iter).sumTabu++;
            }
            return ;
        }

        if (solution == optimum + 1) {
            if (type == ITERATED_LOCAL) {
                (*iter).numNearOptimumILS++;
                (*iter).sumILS++;
            }
            else { //tabu
                (*iter).numNearOptimumTabu++;
                (*iter).sumTabu++;
            }

            return ;
        }



    }
    void getResult() {

        std::cout << "====================================================================" << std::endl;

        std::cout << std::setw(17) << std::left << "Set\t" << "   ILS\t   \t   \t" << "TABOO" << std::endl;
        std::cout << std::setw(17) << std::left << "                      " << "\tOpt\tOpt-1\tSum\tOpt\tOpt-1\tSum" << std::endl;

        std::cout << "--------------------------------------------------------------------" << std::endl;

        std::vector<column>::iterator iter;

        for (iter = columns.begin(); iter != columns.end(); iter++) {
            std::cout   << std::setw(17) << std::left << (*iter).problemSet;
            std::cout
                        << std::right << "\t" << (*iter).numAtOptimumILS
                        << "\t" << (*iter).numNearOptimumILS
                        << "\t" << (*iter).sumILS

                        << "\t" << (*iter).numAtOptimumTabu
                        << "\t" << (*iter).numNearOptimumTabu
                        << "\t" << (*iter).sumTabu
                        << std::endl;
        }

        std::cout << "====================================================================" << std::endl;

    }
    void addRunTime(std::string set, double runtime, searchType searchType) {
        runtimes.push_back({set, runtime, searchType});
    }

    void getRunTimes() {
        // "set" 0.2221 ILS
        std::vector<std::string> sets;

        std::vector<std::string>::iterator iter;

        //make a vector of all the unique sets
        for (runtime r : runtimes) {
            bool found = false;
            for (iter = sets.begin(); iter != sets.end(); iter++)
                if ((*iter) == r.problemSet)
                    found = true;

            if (!found)
                sets.push_back(r.problemSet);
        }

        //loop through the sets and get the average for each search type
        //taboo

        int countTaboo;
        int countILS;
        double totalTaboo;
        double totalILS;
        std::vector<runtimeResult> results;

        for (std::string set : sets) {
            countTaboo = 0;
            totalTaboo = 0;
            countILS = 0;
            totalILS = 0;
            for (runtime r: runtimes) {
                if (r.problemSet == set) {
                    if (r.searchType == TABOO){
                        countTaboo++;
                        totalTaboo += r.runtime;
                    }
                    else {
                        countILS++;
                        totalILS += r.runtime;
                    }
                }
            }

            //push to the results array
            results.push_back({
                set,
                static_cast<double>(totalILS) / countILS,
                static_cast<double>(totalTaboo) / countTaboo
            });

        }

        //print the results

        std::cout << "-----------------------------------" << std::endl;
        std::cout << std::setw(17) << std::left << "SET                \tILS\tTaboo" << std::endl;

        for (runtimeResult r : results)
            std::cout << std::setw(17) << std::left << r.problemSet << "\t" << r.ILSRuntime << "\t" << r.TabooRuntime << std::endl;

        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Avg                     " << totalILS << "ms\t" << totalTaboo << "ms" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
};