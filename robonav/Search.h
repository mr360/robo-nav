/*
    Search.h
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#pragma once

#include <vector>
#include "Map.h"

class Search {
    private:
        std::vector<std::vector<Map>> mapMaze;
        std::vector<int> mapList;
        // output array
    public:
        // Default constuctor
        Search();

        void generateMap();

        friend std::istream& operator >> (std::istream& aIStream, Search& aObject);
        friend std::ostream& operator << (std::ostream& aOStream, Search& aObject);

        Node getDimension();
        Node getStartPos();
        Node getFinishPos();

        // Search Methods
        void bfs();
        void dfs();

        void vis();      // gui testing
        void aStar();
        //void gbfs();
};