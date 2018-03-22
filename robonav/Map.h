/*
    Map.h
    Date: 15/03/18
    Author: 101119509
    Description: Store robotic map co-ord & process I/O tasks, such as
                 reading & outputting to file.
*/

#pragma once
#include <iostream>

constexpr uint8_t MAX_LIST = 55;
constexpr uint8_t MAX_SUB_LIST = 4;

class Map
{
    private:
        uint16_t mapList[MAX_LIST][MAX_SUB_LIST];
        uint16_t nodePathTaken;
    public:
        // Default constructor (initializes all member variables)
        Map();

        //createMapLayout();
            //Setup array size [N]*[M]
            //Insert start & end position of Agent
            //Insert walls  

        // Input operator for Map
        friend std::istream& operator >> (std::istream& aIStream, Map& aObject);

        // Output operator for Map
        friend std::ostream& operator << (std::ostream& aOStream, const Map& aObject);
};