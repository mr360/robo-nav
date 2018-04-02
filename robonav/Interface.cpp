/*
    Interface.cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]                 
*/

#include "interface.h"
#include <fstream>

#include "search/inform/CUS1.h"
#include "search/inform/DFS.h"
#include "search/inform/BFS.h"

#include "search/uninform/CUS2.h"
#include "search/uninform/GBFS.h"
#include "search/uninform/AS.h"

// Comand line arguments
constexpr int ARG_PREFIX = 0;
constexpr int METHOD = 1;
constexpr int SEARCH = 2;
constexpr int OUTPUT = 3;
constexpr int INPUT_FILENAME = 1;
constexpr int OUTPUT_FILENAME = 4;

// Search Methods 
constexpr char CUS1 = 'u';
constexpr char DFS = 'd';
constexpr char BFS = 'b';
constexpr char CUS2 = 'i';
constexpr char GBFS = 'g';
constexpr char AS = 'a';

void selectSearchAlgorithm(char *argv[], Map& aObject) {
    if (argv[SEARCH][ARG_PREFIX] == '-') {
        switch (argv[SEARCH][METHOD]) {
            // Informed Search
            case CUS1: CUS1Func(aObject);  
                       break;
            case DFS:  DFSFunc(aObject);   
                       break;
            case BFS:  BFSFunc(aObject);   
                       break;
            // Uninformed Search
            case CUS2: CUS2Func(aObject);  
                       break;
            case GBFS: GBFSFunc(aObject);  
                       break;
            case AS:   ASFunc(aObject);    
                       break;
            default:   std::cout << "Unknown search argument!"; 
                       break;
        }
    }
}

bool readData(char *argv[], Map& aObject) {
    std::ifstream file{ argv[INPUT_FILENAME], std::ios_base::in };
    if (!file) return false;
    file >> aObject;
    file.close();
    return true;
}

bool writeData(char *argv[], Map& aObject) {
    if (argv[OUTPUT][ARG_PREFIX] == '-' && argv[OUTPUT][METHOD] == 'o') {
        std::ofstream file{ argv[OUTPUT_FILENAME], std::ios_base::out };
        if (!file) return false;   // ADD FEATURE::Check if aObject is empty
        file << aObject;
        return true;
    }
    return false;
}

