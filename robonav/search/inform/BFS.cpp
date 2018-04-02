/*
    [filename].cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#include "BFS.h"


void BFSFunc(Map& aObject) {
    std::cout << "BFS Search: Queue FIFO" << std::endl;
    std::vector<char> BFSMap;

    aObject.createMapLayout(BFSMap);

    BFSMap[0,1];
    
    // Write results
    // Print to screen 

    // Once done call map class destroy
    aObject.~Map();
}