/*
    Search.h
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#pragma once

#include <vector>
#include "Node.h"

class Search {
    private:
        std::vector<std::vector<Node>> mapMaze;
        std::vector<int> mapList;
        // output array
    public:
        void generateMap();

        friend std::istream& operator >> (std::istream& aIStream, Search& aObject);
        friend std::ostream& operator << (std::ostream& aOStream, Search& aObject);

        Coord getDimension();
        Coord getStartPos();
        Coord getFinishPos();

        // Search Methods
        void bfs();
        void dfs();
        void aStar();
        void gbfs();

        void cus01();
        void cus02();

        void vis();      // gui testing

};