/*
Node.h
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

struct Coord
{
    int x;
    int y;
};

class Node
{
    private:
        // Coord
        int x;
        int y;

        // Flags
        bool visitFlag;
        bool pendingVisitFlag;
        bool wallFlag;
        bool finishFlag;
        bool startFlag;

        // Storage of Edges and Parent node
        Coord edge[EDGE_AMOUNT];
        Coord parent;

        // Informed Search 
        // A* only --> Dedicated getters and setters to generate these scores
        int hScore;
        int gScore;
        int fScore;

    public:
        // Default constuctor
        Node();
        // Overload constructor
        Node(int, int);

        // Getters for score
        int getGScore() const;
        int getHScore() const;
        int getFScore() const;

        // Getters for coords
        int getX();
        int getY();

        // Getter for parent coords
        int getParentX();
        int getParentY();

        // Setters for score
        void setGScore(int);
        void setHScore(int);
        void setFScore(int);

        // Search tools
        bool isNotVisited();
        bool isNotPendingVisit();

        bool isNotWall();
        bool isValidEdge(int);

        void setVisitFlag(bool);
        void setPendingVisit(bool);

        bool isFinish();
        bool isStart();

        Coord getEdge(int);
        void setParent(Node& n);

        // Add node details
        void setWall();
        void setStart();
        void setFinish();
        void generateEdges(Coord& mapDim);
        void generateScore(Coord& finishNode);

};

