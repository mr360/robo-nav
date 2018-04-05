/*
    Map.cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#include "Map.h"

Map::Map()
{
    x = 0;
    y = 0;
    visitFlag = false;
    wallFlag = false;
    finishFlag = false;
    startFlag = false;

}

Map::Map(int ix, int iy)
{
    x = ix;
    y = iy;
    visitFlag = false;
    wallFlag = false;
    finishFlag = false;
    startFlag = false;

    //Set all edges to out-of-bounds
    for (int i = 0; i < EDGE_AMOUNT; i++) {
        edge[i].x = OUT_OF_BOUND;
        edge[i].y = OUT_OF_BOUND;
    }
}


bool Map::isNotVisited()
{
    if (visitFlag == false) {
        return true;
    }
    return false;
}

bool Map::isNotWall()
{
    if (wallFlag == false) {
        return true;
    }
    return false;
}

bool Map::isValidEdge(int direction)
{
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    if (edge[direction].x != OUT_OF_BOUND) return true;
    return false;
}


bool Map::isFinish()
{
    if (finishFlag == true) {
        return true;
    }
    return false;
}

bool Map::isStart()
{
    if (startFlag == true) {
        return true;
    }
    return false;
}

Node Map::getEdge(int direction)
{
    return edge[direction];
}

void Map::setWall()
{
    wallFlag = true;
}

void Map::setVisitFlag(bool flag)
{
    visitFlag = flag;
}

void Map::setStart()
{
    startFlag = true;
}

void Map::setFinish()
{
    finishFlag = true;
}

void Map::generateEdges(Node & mapDim)
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




