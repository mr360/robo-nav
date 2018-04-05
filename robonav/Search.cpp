/*
    Search.cpp
    Date: 15/03/18
    Author: 101119509
    Description: [Add Details]
*/

#include "Search.h"
#include <iostream>
#include <queue>
#include <stack> 
#include <sstream>
#include <algorithm>

Search::Search()
{
}

void Search::generateMap()
{
    #define dimX (0)
    #define dimY (1)

    // Map dimension
    Node mapDim;
    mapDim.x = mapList[dimX];
    mapDim.y = mapList[dimY];
    int dim_col = mapDim.y;
    int dim_row = mapDim.x;

    // Resize vector 
    mapMaze.resize(dim_row, std::vector<Map>(dim_col, Map()));

    // Set x,y object pos & generate edges
    for (int i = 0; i < dim_row; i++) {
        for (int j = 0; j < dim_col; j++) {
            mapMaze[i][j] = Map(i, j);
            mapMaze[i][j].generateEdges(mapDim);
        }
    }

    // Set wall and agent flags
    for (int i = 2; i < mapList.size(); i += 2) {
        #define AGENT_START (2)
        #define AGENT_FINISH (4)
        #define WALL_SECTION (6)
        int x = mapList[i + 1];
        int y = mapList[i];

        if (i == AGENT_START) mapMaze[x][y].setStart();
        if (i == AGENT_FINISH) mapMaze[x][y].setFinish();
        if (i >= WALL_SECTION) mapMaze[x][y].setWall();
    }
}

Node Search::getFinishPos()
{
    Node fPos;
    fPos.x = mapList[5];
    fPos.y = mapList[4];

    return fPos;
}

Node Search::getDimension()
{
    Node mDim;
    mDim.x = mapList[0];
    mDim.y = mapList[1];

    return mDim;
}

Node Search::getStartPos()
{
    Node sPos;
    sPos.x = mapList[3];
    sPos.y = mapList[2];

    return sPos;
}

std::istream & operator >> (std::istream & aIStream, Search & aObject)
{
    // Store only the integer values
    std::vector<int>result;
    for (std::string s1; aIStream >> s1;)
    {
        s1.erase(std::find(s1.begin(), s1.end(), '['));
        s1.erase(std::find(s1.begin(), s1.end(), ']'));
        s1.erase(std::find(s1.begin(), s1.end(), '('));
        s1.erase(std::find(s1.begin(), s1.end(), ')'));

        std::string s2;
        std::istringstream ss(s1);
        while (std::getline(ss, s2, ','))
        {
            result.push_back(std::stoi(s2));
        }
    }

    #define X result[i]
    #define Y result[i + 1]

    // Process dimension & agents start / finish
    for (int i = 0; i < 6; i += 2) {
        aObject.mapList.push_back(X);
        aObject.mapList.push_back(Y);
    }

    // Process walls
    for (int i = 6; i < result.size(); i += 4) {
        #define CURRENT_BLOCK (1)
        #define Width result[i + 2]
        #define Height result[i + 3]

        // Starting point of the wall
        aObject.mapList.push_back(X);
        aObject.mapList.push_back(Y);

        // If square, generate x,y co-ord 
        if (Width == Height && Width > 1 && Height > 1) {
            aObject.mapList.push_back(X + 1);
            aObject.mapList.push_back(Y + 1);
        }

        // Generate individual x,y co-ord for the width length
        int wallWidth = Width;
        while (wallWidth > 1) {
            aObject.mapList.push_back(X + (wallWidth - CURRENT_BLOCK));
            aObject.mapList.push_back(Y);
            wallWidth--;
        }

        // Generate individual x,y co-ord for the height length
        int wallHeight = Height;
        while (wallHeight > 1) {
            aObject.mapList.push_back(X);
            aObject.mapList.push_back(Y + (wallHeight - CURRENT_BLOCK));
            wallHeight--;
        }

    }

    return aIStream;
}

std::ostream & operator<<(std::ostream & aOStream, Search & aObject)
{
    return aOStream;
}

void Search::vis() {
    // Visualise
    system("cls");
    Node dim = getDimension();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            if (mapMaze[i][j].isFinish()) std::cout << "F";
            if (!(mapMaze[i][j].isNotVisited()) && !(mapMaze[i][j].isFinish() && !(mapMaze[i][j].isStart()))) {
                std::cout << "v";
            }
            else if (((mapMaze[i][j].isNotVisited())) && (mapMaze[i][j].isNotWall())) {
                std::cout << "_";
            }
            else if (!(mapMaze[i][j].isNotWall())) std::cout << "H";
        }
        std::cout << "" << std::endl;
    }
}

void Search::bfs()
{
    generateMap();
    //
    Node start = getStartPos();
    std::queue<Map> bfsQueue;
    Map &root = mapMaze[start.x][start.y];

    // 
    bfsQueue.push(root);
    root.setVisitFlag(true);

    //
    while (!bfsQueue.empty()) {
        vis();  // Testing visualise
        Map current = bfsQueue.front();
        bfsQueue.pop();

        if (current.isFinish()) {
            std::cout << "BFS: Found Finish" << std::endl;
            break;
        }

        //
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Map &future = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (future.isNotWall() && future.isNotVisited()) {
                    bfsQueue.push(future);
                    future.setVisitFlag(true);
                }
            }
        }
    }
}


void Search::dfs()
{
    generateMap();
    //
    Node start = getStartPos();
    std::stack<Map> dfsStack;
    Map &root = mapMaze[start.x][start.y];

    // 
    dfsStack.push(root);
    root.setVisitFlag(true);

    //
    while (!dfsStack.empty()) {
        vis();  // Testing visualise
        Map current = dfsStack.top();
        dfsStack.pop();

        if (current.isFinish()) {
            std::cout << "DFS: Found Finish" << std::endl;
            break;
        }

        //
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Map &future = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (future.isNotWall() && future.isNotVisited()) {
                    dfsStack.push(future);
                    future.setVisitFlag(true);
                }
            }
        }
    }
}




