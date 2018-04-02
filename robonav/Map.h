/*
    Map.h
    Date: 15/03/18
    Author: 101119509
    Description: Store robotic map co-ord & process I/O tasks, such as
                 reading & outputting to file.
*/

#pragma once
#include <iostream>
#include <vector>

constexpr int8_t DEFAULT_VALUE = -99;
constexpr uint8_t COLUMN_NUM = 4;
constexpr uint8_t ROW_NUM = 25;

class Map
{
    private:
        std::vector<std::vector<int16_t>> mapList;
        int16_t nodePathTaken;
    public:
        // Default constructor (initializes all member variables)
        Map();

        // Destroy the map class 
        ~Map();

        // Getters and Setters
        unsigned int getDimension(char coord);
        unsigned int getAgent(char pos);

        // Create and populate map
        void createWallLayout(std::vector<char>& algoMap);
      
        // Input operator for Map
        friend std::istream& operator >> (std::istream& aIStream, Map& aObject);

        // Output operator for Map
        friend std::ostream& operator << (std::ostream& aOStream, const Map& aObject);
};