/*
    main.cpp
    Date: 15/03/18
    Author: 101119509
    Description: Robotic Finder.
*/

#include <iostream>
#include "Map.h"
#include "interface.h"

int main(int argc, char* argv[]) {   
    if (argc < 5) {
        std::cerr <<  "Incomplete argument list!\n"
                  <<  "Usage: search.exe <input_file> <method> <output> <output_file>";
        return -1;
    }

    Map route01;
    if (loadData(argv, route01)) {
        selectSearchAlgorithm(argv, route01);
        if (!unloadData(argv, route01)) {
            std::cerr << "Write to file failed!" << std::endl;
        }
    }
    else std::cerr << "File cannot be opened!" << std::endl;

    return 0;
}