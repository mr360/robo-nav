/*
    main.cpp
    Date: 15/03/18
    Author: 101119509
    Description: Robotic Finder.
*/

#include <iostream>
#include "interface.h"

int main(int argc, char* argv[]) {   
    if (argc < 4) {
        std::cerr <<  "Incomplete argument list!\n"
                  <<  "Usage: search.exe <input_file> <method> <output_file>";
        return -1;
    }

    Search map;
    if (readData(argv, map)) {
        selectSearchAlgorithm(argv, map);
        writeData(argv, map);
    }

    return 0;
}