/*
    Map.cpp
    Date: 15/03/18
    Author: 101119509
    Description: Store robotic map co-ord & process I/O tasks, such as
                 reading & outputting to file.
*/

#include "Map.h"

Map::Map()
{
    nodePathTaken = 0;

    for (int i = 0; i < MAX_LIST; i++) {
        for (int j = 0; j < MAX_SUB_LIST; j++) {
            mapList[i][j] = 0;
        }
    }
}

std::istream& operator >> (std::istream& aIStream, Map& aObject)
{
      
    return aIStream;
}

std::ostream& operator << (std::ostream& aOStream, const Map& aObject)
{
    //FILE STRUCTURE: filename method number_of_nodes path 
    return aOStream;
}
