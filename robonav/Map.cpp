/*
    Map.cpp
    Date: 15/03/18
    Author: 101119509
    Description: Store robotic map co-ord & process I/O tasks, such as
                 reading & outputting to file.
*/

#include "Map.h"
#include <string>

Map::Map()
{
   nodePathTaken = 0;
   mapList.resize(ROW_NUM, std::vector<int16_t>(COLUMN_NUM, DEFAULT_VALUE));
}

Map::~Map()
{
    // Delete map class object
}

unsigned int Map::getDimension(char coord)
{
    //Setup array size [N]*[M]
    return 0;
}

unsigned int Map::getAgent(char pos)
{
    //Insert start & end position of Agent
    return 0;
}

void Map::createWallLayout(std::vector<char>& algoMap)
{
    //Setup array size [N]*[M]
    //unsigned int N = mapList[0][0];
    //unsigned int M = mapList[0][1];
    //algoMap.resize(N, std::vector<char>(M, DEFAULT_VALUE));
    //Insert start & end position of Agent
    //Insert walls 
}

std::istream& operator >> (std::istream& aIStream, Map& aObject)
{
    #define START_MAIN_COORD ('X')
    #define SEPARATOR ('Z')

    // Map boundry characters to string processor friendly characters
    std::string temp;
    for (char input; aIStream >> input;) {
        if (input == '[' || input == '(') temp.push_back(START_MAIN_COORD);
        if (input == ',') temp.push_back(SEPARATOR);
        if (isdigit(input)) temp.push_back(input);
    }

    // Mapped to aObject[m][k] array
    int m = -1;         // Starts at index 0
    int k = 0;

    // Process the ugly formatting of the input file
    for (unsigned int i = 0; i < temp.size(); i++) {
        // Every new co-ord reset sub listing co-ord (k) counter
        if (temp[i] == START_MAIN_COORD) {
            m++;
            k = 0;
        }
        // Increment sub-listing counter (k)
        if (temp[i] == SEPARATOR) k++;
        
        // Process double digit, e.g 11-99
        // Check if |digit|digit|
        if (isdigit(temp[i]) && isdigit(temp[i+1])) {
            std::string x;
            x.push_back(temp[i]);
            x.push_back(temp[i + 1]);

            aObject.mapList[m][k] = stoi(x);
        }

        // Process single digit, e.g 1-9
        // Check if |not digit|digit|not digit|
        if (isdigit(temp[i]) && !isdigit(temp[i + 1]) && !isdigit(temp[i - 1])) {
            aObject.mapList[m][k] = static_cast<int>(temp[i] - '0');
        }
    }
    
    return aIStream;
}

std::ostream& operator<< (std::ostream& aOStream, const Map& aObject)
{
    //FILE STRUCTURE: filename method number_of_nodes path 
    return aOStream;
}
