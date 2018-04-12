/*
    Node.cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#include "Node.h"
#include <cmath>

Node::Node()
{
    // Coord
    x = 0;
    y = 0;

    // Flags
    visitFlag = false;
    pendingVisitFlag = false;
    wallFlag = false;
    finishFlag = false;
    startFlag = false;

    // Informed Search (A* GBFS)
    hScore = 0;
    gScore = 0;
    fScore = 0;

}

Node::Node(int ix, int iy)
{
    // Coord
    x = ix;
    y = iy;

    // Flags
    visitFlag = false;
    pendingVisitFlag = false;
    wallFlag = false;
    finishFlag = false;
    startFlag = false;

    //Set all edges to out-of-bounds
    for (int i = 0; i < EDGE_AMOUNT; i++) {
        edge[i].x = OUT_OF_BOUND;
        edge[i].y = OUT_OF_BOUND;
    }

    //Set parent to out-of-bound
    parent.x = OUT_OF_BOUND;
    parent.y = OUT_OF_BOUND;

    // Informed Search (A* GBFS)
    hScore = 0;
    gScore = 0;
    fScore = 0;
}

int Node::getGScore() const
{
    return gScore;
}

int Node::getHScore() const
{
    return hScore;
}

int Node::getFScore() const
{
    return fScore;
}

void Node::setGScore(int gVal)
{
    gScore = gVal;
}

void Node::setHScore(int hVal)
{
    hScore = hVal;
}

void Node::setFScore(int fVal)
{
    fScore = fVal;
}

bool Node::isNotVisited()
{
    if (visitFlag == false) return true;
    return false;
}

bool Node::isNotPendingVisit()
{
    if (pendingVisitFlag == false) return true;
    return false;
}

bool Node::isNotWall()
{
    if (wallFlag == false) return true;
    return false;
}

bool Node::isValidEdge(int direction)
{
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    return false;
}

bool Node::isFinish()
{
    if (finishFlag == true) return true;
    return false;
}

bool Node::isStart()
{
    if (startFlag == true) return true;
    return false;
}

Coord Node::getEdge(int direction)
{
    return edge[direction];
}

void Node::setParent(Node & n)
{
    parent.x = n.x;
    parent.y = n.y;
}

void Node::setWall()
{
    wallFlag = true;
}

void Node::setVisitFlag(bool flag)
{
    visitFlag = flag;
}

void Node::setPendingVisit(bool flag)
{
    pendingVisitFlag = flag;
}

void Node::setStart()
{
    startFlag = true;
}

void Node::setFinish()
{
    finishFlag = true;
}

void Node::generateEdges(Coord& mapDim)
{
    int dim_col = mapDim.y - ZEROth_ARRAY;
    int dim_row = mapDim.x - ZEROth_ARRAY;
    
    bool leftEdge = true;
    bool upEdge = true;
    bool downEdge = true;
    bool rightEdge = true;

    // Check bounds
    if (y <= 0)        leftEdge = false;
    if (x <= 0)        upEdge = false;
    if (x >= dim_row)  downEdge = false;
    if (y >= dim_col)  rightEdge = false;
    
    // Set the Node neighbouring edges
    if (upEdge) { 
        edge[UP].x = (x - 1);
        edge[UP].y = y;
    }    
    
    if (leftEdge) {
        edge[LEFT].y = (y - 1);
        edge[LEFT].x = x;
    }

    if (downEdge) {
        edge[DOWN].x = (x + 1);
        edge[DOWN].y = y;
    }

    if (rightEdge) {
        edge[RIGHT].y = (y + 1);
        edge[RIGHT].x = x;
    }
}

void Node::generateScore(Coord& finishNode)
{
    if (isNotWall()) {
        hScore = abs(finishNode.x - x) + abs(finishNode.y - y);
        gScore = 0;
    }
}




