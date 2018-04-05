/*
    Map.h
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#pragma once
#define UP (0)
#define LEFT (1)
#define DOWN (2)
#define RIGHT (3)
#define EDGE_AMOUNT (4)
#define OUT_OF_BOUND (-1)
#define ZEROth_ARRAY (1)

struct Node {
    int x;
    int y;
};

class Map {
    private:
        int x;
        int y;
    
        bool visitFlag;
        bool wallFlag;
        bool finishFlag;
        bool startFlag;

        Node edge[EDGE_AMOUNT];
    
        // A* only --> Dedicated getters and setters to generate these scores
        //int hScore;
        //int gScore;
        //int fScore = hScore + gScore;

    public:
        // Default constuctor
        Map();                              
        // Overload constructor
        Map(int, int);                      

        // Search tools
        bool isNotVisited();
        bool isNotWall();
        bool isValidEdge(int);
        void setVisitFlag(bool);

        bool isFinish();
        bool isStart();
        Node getEdge(int);

        // Add map details
        void setWall();
        void setStart();
        void setFinish();
        void generateEdges(Node& mapDim);  

};

