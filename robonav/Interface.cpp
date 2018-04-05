/*
    Interface.cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]                 
*/

#include "interface.h"
#include <fstream>
#include <iostream>
#include "Search.h"

// Comand line arguments
constexpr int ARG_PREFIX = 0;
constexpr int METHOD = 1;
constexpr int SEARCH = 2;
constexpr int INPUT_FILENAME = 1;
constexpr int OUTPUT_FILENAME = 3;

// Search Methods 
constexpr char CUS1 = 'u';
constexpr char DFS = 'd';
constexpr char BFS = 'b';
constexpr char CUS2 = 'i';
constexpr char GBFS = 'g';
constexpr char AS = 'a';

void selectSearchAlgorithm(char *argv[], Search& aObject) {
    if (argv[SEARCH][ARG_PREFIX] == '-') {
        switch (argv[SEARCH][METHOD]) {
            // Informed Search
            case CUS1: //aObject.cus01();
                       break;
            case DFS:  aObject.dfs();
                       break;
            case BFS:  aObject.bfs();
                       break;
            // Uninformed Search
            case CUS2: //aObject.cus02();
                       break;
            case GBFS: //aObject.gbfs();
                       break;
            case AS:   //aObject.aStar();
                       break;
            default:   std::cout << "Unknown search argument!"; 
                       break;
        }
    }
}

bool readData(char *argv[], Search& aObject) {
    std::ifstream file{ argv[INPUT_FILENAME], std::ios_base::in };
    if (!file) {
        std::cerr << "File cannot be read" << std::endl;
        return false;
    }
    file >> aObject;
    file.close();
    return true;
}

bool writeData(char *argv[], Search& aObject) {
    std::ofstream file{ argv[OUTPUT_FILENAME], std::ios_base::out };
    if (!file) {
        std::cerr << "Data cannot be written" << std::endl;
        return false;
    }
    file << aObject;
    return true;
}

