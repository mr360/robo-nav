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
#include <vector>

void Search::generateMap()
{
    // Map dimension
    Coord mapDim = getDimension();
    int dim_col = mapDim.y;
    int dim_row = mapDim.x;

    // Start / Finish pos
    Coord finishPos= getFinishPos();
    Coord startPos = getStartPos();

    // Resize vector
    mapMaze.resize(dim_row, std::vector<Node>(dim_col, Node()));

    // Set x,y object pos & generate edges
    #define DEFAULT_HIGH_COST (9000)
    for (int i = 0; i < dim_row; i++) {
        for (int j = 0; j < dim_col; j++) {
            mapMaze[i][j] = Node(i, j);
            mapMaze[i][j].generateEdges(mapDim);
            mapMaze[i][j].generateScore(finishPos);
            mapMaze[i][j].setGScore(DEFAULT_HIGH_COST);
        }
    }

    // Set agent start and finish flags
    mapMaze[startPos.x][startPos.y].setStart();
    mapMaze[finishPos.x][finishPos.y].setFinish();

    // Set wall
    #define WALL_SECTION (6)
    for (int i = WALL_SECTION; i < mapList.size(); i += 2) {
        int x = mapList[i + 1];
        int y = mapList[i];
        mapMaze[x][y].setWall();
    }
}

Coord Search::getFinishPos()
{
    Coord fPos;
    fPos.x = mapList[5];
    fPos.y = mapList[4];

    return fPos;
}

Coord Search::getDimension()
{
    Coord mDim;
    mDim.x = mapList[0];
    mDim.y = mapList[1];

    return mDim;
}

Coord Search::getStartPos()
{
    Coord sPos;
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

void Search::cus01()
{
    std::cout << "Custom01" << std::endl;
}

void Search::cus02()
{
    std::cout << "Custom02" << std::endl;
}

void Search::vis() {
    // Visualise
    system("cls");
    Coord dim = getDimension();
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            if (mapMaze[i][j].isFinish()) std::cout << "F";
            if (!(mapMaze[i][j].isNotVisited()) && !(mapMaze[i][j].isFinish() && !(mapMaze[i][j].isStart())) && (mapMaze[i][j].isNotPendingVisit())) {
                std::cout << "v";
            }
            else if (!(mapMaze[i][j].isNotPendingVisit())) {
                std::cout << "p";
            }
            else if (((mapMaze[i][j].isNotVisited())) && (mapMaze[i][j].isNotWall())) {
                std::cout << "_";
            }
            else if (!(mapMaze[i][j].isNotWall())) std::cout << "H";
        }
        std::cout << "" << std::endl;
    }

    // Visualise h-scores
    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            std::cout<< "[" << mapMaze[i][j].getHScore() << "]";
        }
        std::cout << "" << std::endl;
    }
}

struct lowestFScore {
    bool operator()(const Node& lhs, const Node& rhs) const {
        return lhs.getFScore() < rhs.getFScore();
    }
};

void Search::aStar()
{
    generateMap();

    std::queue<Node> nodeHistory;
    //std::priority_queue<Node, std::vector<std::reference_wrapper<Node>>, comp> openSet;
    std::vector<std::reference_wrapper<Node>> openSet;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    openSet.push_back(root);
    root.setVisitFlag(true);

    root.setGScore(0);

    while (!openSet.empty()) {
        vis();  // Testing visualise
        std::sort(openSet.begin(), openSet.end(), lowestFScore());
        Node &current = openSet.front();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        openSet.erase(openSet.begin());

        // Add to list of visited nodes 
        nodeHistory.push(current);

        if (current.isFinish()) {
            std::cout << "A*: Found Finish" << std::endl;
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                // If not a wall and has been visited, ignore
                if (neighbor.isNotWall() && !(neighbor.isNotVisited())) continue;

                // If not in openset, add it and set flag
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit()) {
                    // Add to queue and set flag
                    openSet.push_back(neighbor);
                    neighbor.setPendingVisit(true);
                }

                // Calculate gScore, and see if it is better than neigbours current score.
                #define MOVEMENT_COST (1)
                int tentativeGScore = current.getGScore() + MOVEMENT_COST;
                if (tentativeGScore >= neighbor.getGScore()) continue;
                
                // This path is the best until now. Record it!
                neighbor.setParent(current);
                neighbor.setGScore(tentativeGScore);
                int fScore = neighbor.getGScore() + neighbor.getHScore();
                neighbor.setFScore(fScore);
            }
        }
    }
}

void Search::gbfs()
{
    generateMap();

    std::queue<Node> nodeHistory;
    //std::priority_queue<Node, std::vector<std::reference_wrapper<Node>>, comp> openSet;
    std::vector<std::reference_wrapper<Node>> openSet;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    openSet.push_back(root);
    root.setVisitFlag(true);

    root.setGScore(0);

    while (!openSet.empty()) {
        vis();  // Testing visualise
        std::sort(openSet.begin(), openSet.end(), lowestFScore());
        Node &current = openSet.front();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        openSet.erase(openSet.begin());

        // Add to list of visited nodes 
        nodeHistory.push(current);

        if (current.isFinish()) {
            std::cout << "GBFS: Found Finish" << std::endl;
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                // If not a wall and has been visited, ignore
                if (neighbor.isNotWall() && !(neighbor.isNotVisited())) continue;

                // If not in openset, add it and set flag
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit()) {
                    // Add to queue and set flag
                    openSet.push_back(neighbor);
                    neighbor.setPendingVisit(true);
                }

                // Set parent and set path least away from end goal
                neighbor.setParent(current);
                neighbor.setFScore(neighbor.getHScore());
            }
        }
    }
}

void Search::bfs()
{
    generateMap();

    std::queue<Node> nodeHistory;
    std::queue<std::reference_wrapper<Node>> bfsQueue;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    bfsQueue.push(root);
    root.setVisitFlag(true);

    while (!bfsQueue.empty()) {
        vis();  // Testing visualise
        Node &current = bfsQueue.front();
        
        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Remove evaluated node from queue
        bfsQueue.pop();

        // Add to list of visited nodes 
        nodeHistory.push(current);

        if (current.isFinish()) {
            std::cout << "BFS: Found Finish" << std::endl;
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit()) {
                    // Set the parent node for surrounding nodes
                    neighbor.setParent(current);
                    // Add to queue and set flag
                    bfsQueue.push(neighbor);
                    neighbor.setPendingVisit(true);
                }
            }
        }
    }
}

void Search::dfs()
{
    generateMap();

    std::queue<Node> nodeHistory;
    std::stack<std::reference_wrapper<Node>> dfsStack;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y]; 
    dfsStack.push(root);
    root.setVisitFlag(true);

    while (!dfsStack.empty()) {
        vis();  // Testing visualise
        Node current = dfsStack.top();
       
        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Remove evaluated node from queue
        dfsStack.pop();

        // Add to list of visited nodes 
        nodeHistory.push(current);

        if (current.isFinish()) {
            std::cout << "DFS: Found Finish" << std::endl;
            break;
        }

        // Add each valid edges node to the stack
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit()) {
                    // Set the parent node for surrounding nodes
                    neighbor.setParent(current);
                    // Add to queue and set flag
                    dfsStack.push(neighbor);
                    neighbor.setPendingVisit(true);
                }
            }
        }
    }
}




