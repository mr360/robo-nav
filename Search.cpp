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

#define MOVEMENT_COST (1)

void Search::guiOpen(LPSTR title, int width, int height)
{
    WNDCLASS windowClass;
    HINSTANCE hInstance = NULL;

    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = guiWndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;

    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = "guiWindow";
    RegisterClass(&windowClass);


    guiHwnd = CreateWindow(
        "guiWindow",         // class name
        title,              // title
        WS_OVERLAPPED,      // style
        CW_USEDEFAULT,      // x position
        CW_USEDEFAULT,      // y position
        width,              // x size
        height,             // y size
        GetActiveWindow(),  // parent
        NULL,               // menu ptr
        hInstance,          // app instance
        NULL);              // init params

    graphics = new Graphics();
    if (!graphics->Init(guiHwnd))
    {
        delete graphics;
    }
    
    ShowWindow(guiHwnd, SW_SHOWNORMAL);
}

void Search::guiDraw(Node& cell)
{
    #define GRID (10)
    #define BORDER (50)
    int posHorizontal = cell.getX() * GRID + BORDER;
    int posVertical = cell.getY() * GRID + BORDER;
    
    graphics->BeginDraw();

    // If path has not been generated, search is still underway
    // If path elements > 0, draw the path
    if (path.size() == 0)
    {
        if (!cell.isNotPendingVisit())  graphics->DrawCell(posHorizontal, posVertical, 1, 0.561f, 0.725f, 0.561f, 0.5f);
        if (!cell.isNotWall())          graphics->DrawCell(posHorizontal, posVertical, 1, 0.41f, 0.412f, 0.41f, 1.0f);
        if (!cell.isNotVisited())       graphics->DrawCell(posHorizontal, posVertical, 1, 0.0f, 1.0f, 1.0f, 0.5f);
        if (cell.isStart())             graphics->DrawCell(posHorizontal, posVertical, 1, 1.0f, 1.0f, 0.0f, 1.0f);
        if (cell.isFinish())            graphics->DrawCell(posHorizontal, posVertical, 1, 0.0f, 1.0f, 0.0f, 1.0f);
    }
    else graphics->DrawCell(posHorizontal, posVertical, 1, 1.0f, 1.0f, 0.0f, 1.0f);
    
    graphics->EndDraw();
    
}

void Search::guiRefresh(Node& cell)
{
    // Get the console output up to date
    #if defined(_INC_OSTREAM)
    std::cout.flush();
    #endif
    std::fflush(stdout);
    std::fflush(stderr);

    // If graphics window is not open, exit harmlessly
    if (!guiHwnd) return;

    // Get the contents of the window up to date
    UpdateWindow(guiHwnd);

    // Allow for redraw
    guiDraw(cell);

    MSG msg;
    if (PeekMessage(&msg, guiHwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Search::guiShowWall()
{
    Node wall;
    #define WALL_SECTION (6)
    for (unsigned int i = WALL_SECTION; i < mapList.size(); i += 2)
    {
        int x = mapList[i + 1];
        int y = mapList[i];
        
        wall = mapMaze[x][y];
        
        guiRefresh(wall);
    }
}

void Search::guiShowConstructedPath()
{
    for (unsigned int i = 0; i < path.size(); i++)
    {
        guiRefresh(path[i]);
    }
}

void Search::guiClose()
{
    delete graphics;
    DestroyWindow(guiHwnd);  // sends WM_DESTROY message
}

LRESULT Search::guiWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }
    else if (message == WM_PAINT)  return 0;
    else return (DefWindowProc(hWnd, message, wParam, lParam));
}

Search::Search()
{
    searchMethod = "NONE";
}

Search::~Search()
{
}

void Search::generateMap()
{
    // Map dimension
    Coord mapDim = getDimension();
    int dim_col = mapDim.y;
    int dim_row = mapDim.x;

    // Start / Finish pos
    Coord finishPos = getFinishPos();
    Coord startPos = getStartPos();

    // Resize vector
    mapMaze.resize(dim_row, std::vector<Node>(dim_col, Node()));

    // Set x,y object pos & generate edges
    #define DEFAULT_HIGH_COST (9000)
    for (int i = 0; i < dim_row; i++)
    {
        for (int j = 0; j < dim_col; j++)
        {
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
    for (unsigned int i = WALL_SECTION; i < mapList.size(); i += 2)
    {
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
    for (int i = 0; i < 6; i += 2)
    {
        aObject.mapList.push_back(X);
        aObject.mapList.push_back(Y);
    }

    // Process walls
    for (unsigned int i = 6; i < result.size(); i += 4)
    {
        #define CURRENT_BLOCK (1)
        #define Width result[i + 2]
        #define Height result[i + 3]

        // Starting point of the wall
        aObject.mapList.push_back(X);
        aObject.mapList.push_back(Y);

        // If square, generate x,y co-ord 
        if (Width == Height && Width > 1 && Height > 1)
        {
            aObject.mapList.push_back(X + 1);
            aObject.mapList.push_back(Y + 1);
        }

        // Generate individual x,y co-ord for the width length
        int wallWidth = Width;
        while (wallWidth > 1)
        {
            aObject.mapList.push_back(X + (wallWidth - CURRENT_BLOCK));
            aObject.mapList.push_back(Y);
            wallWidth--;
        }

        // Generate individual x,y co-ord for the height length
        int wallHeight = Height;
        while (wallHeight > 1)
        {
            aObject.mapList.push_back(X);
            aObject.mapList.push_back(Y + (wallHeight - CURRENT_BLOCK));
            wallHeight--;
        }

    }
    return aIStream;
}

std::ostream & operator<<(std::ostream & aOStream, Search & aObject)
{
    // Print out path solution
    // Structure: search method, nodes taken and list of steps to finish
    if (aObject.path.size() == 0)
    {
        aOStream << "No solution found" << std::endl;
    }
    else
    {
        aOStream << aObject.searchMethod
                 << "\n" 
                 << aObject.path.size() 
                 << std::endl;

        for (size_t i = aObject.path.size() - 1 ; i > 0 ; i--)
        {
            aOStream << "("
                     << aObject.path[i].getX()
                     << "," 
                     << aObject.path[i].getY()
                     << ")"
                     << std::endl;
        }
    }
    
    return aOStream;
}

struct lowestFScore
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        return lhs.getFScore() > rhs.getFScore();
    }
};

void Search::aStar()
{
    searchMethod = "ASTAR";
    generateMap();

    // Draw Window and wall
    guiOpen("VisX", 800, 600);
    guiShowWall();

    std::vector<Node> nodeHistory;
    std::priority_queue<Node&, std::vector<std::reference_wrapper<Node>>, lowestFScore> openSet;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    openSet.push(root);
    root.setVisitFlag(true);

    root.setGScore(0);

    while (!openSet.empty())
    {
        // Put the minimium fscore element to the front 
        std::make_heap(const_cast<std::reference_wrapper<Node>*>(&openSet.top()),
                       const_cast<std::reference_wrapper<Node>*>(&openSet.top()) + openSet.size(),
                       lowestFScore());

        Node &current = openSet.top();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Update the GUI display
        guiRefresh(current);

        openSet.pop();

        // Add to list of visited nodes 
        nodeHistory.push_back(current);

        if (current.isFinish())
        {
            std::cout << "[Informed] A*: Found Finish"
                      << "\nNote: Speed of search has been slowed down by GUI display."
                      << std::endl;

            // Construct path & update GUI with path
            constructPath(nodeHistory);
            guiShowConstructedPath();

            guiClose();
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++)
        {
            if (current.isValidEdge(i))
            {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                // If not a wall and has been visited, ignore
                if (neighbor.isNotWall() && !(neighbor.isNotVisited())) continue;

                // If not in openset, add it and set flag
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit())
                {
                    // Add to queue and set flag
                    openSet.push(neighbor);
                    neighbor.setPendingVisit(true);

                    // Update the GUI display
                    guiRefresh(neighbor);
                }

                // Calculate gScore, and see if it is better than neigbours current score.
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
    searchMethod = "GBFS";
    generateMap();

    // Draw Window
    guiOpen("VisX", 800, 600);
    guiShowWall();

    std::vector<Node> nodeHistory;
    std::priority_queue<Node&, std::vector<std::reference_wrapper<Node>>, lowestFScore> openSet;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    openSet.push(root);
    root.setVisitFlag(true);

    root.setGScore(0);

    while (!openSet.empty())
    {
        // Put the minimium fscore element to the front 
        std::make_heap(const_cast<std::reference_wrapper<Node>*>(&openSet.top()),
                       const_cast<std::reference_wrapper<Node>*>(&openSet.top()) + openSet.size(),
                       lowestFScore());

        Node &current = openSet.top();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Update the GUI display
        guiRefresh(current);

        openSet.pop();

        // Add to list of visited nodes 
        nodeHistory.push_back(current);

        if (current.isFinish())
        {
            std::cout << "[Informed] GBFS: Found Finish" 
                      << "\nNote: Speed of search has been slowed down by GUI display."
                      << std::endl;

            // Construct path & update GUI with path
            constructPath(nodeHistory);
            guiShowConstructedPath();

            guiClose();
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++)
        {
            if (current.isValidEdge(i))
            {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                // If not a wall and has been visited, ignore
                if (neighbor.isNotWall() && !(neighbor.isNotVisited())) continue;

                // If not in openset, add it and set flag
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit())
                {
                    // Add to queue and set flag
                    openSet.push(neighbor);
                    neighbor.setPendingVisit(true);

                    // Update the GUI display
                    guiRefresh(neighbor);
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
    searchMethod = "BFS";
    generateMap();

    // Draw Window
    guiOpen("VisX", 800, 600);
    guiShowWall();

    std::vector<Node> nodeHistory;
    std::queue<std::reference_wrapper<Node>> bfsQueue;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    bfsQueue.push(root);
    root.setVisitFlag(true);

    while (!bfsQueue.empty())
    {
        Node &current = bfsQueue.front();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Update the GUI display
        guiRefresh(current);

        // Remove evaluated node from queue
        bfsQueue.pop();

        // Add to list of visited nodes 
        nodeHistory.push_back(current);

        if (current.isFinish())
        {
            std::cout << "[Uniformed] BFS: Found Finish"
                      << "\nNote: Speed of search has been slowed down by GUI display."
                      << std::endl;

            // Construct path & update GUI with path
            constructPath(nodeHistory);
            guiShowConstructedPath();

            guiClose();
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++)
        {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit())
                {
                    // Set the parent node for surrounding nodes
                    neighbor.setParent(current);

                    // Add to queue and set flag
                    bfsQueue.push(neighbor);
                    neighbor.setPendingVisit(true);

                    // Update the GUI display
                    guiRefresh(neighbor);
                }
            }
        }
    }
}

void Search::dfs()
{
    searchMethod = "DFS";
    generateMap();

    // Draw Window
    guiOpen("VisX", 800, 600);
    guiShowWall();

    std::vector<Node> nodeHistory;
    std::stack<std::reference_wrapper<Node>> dfsStack;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    dfsStack.push(root);
    root.setVisitFlag(true);

    while (!dfsStack.empty())
    {
        Node &current = dfsStack.top();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Update the GUI display
        guiRefresh(current);

        // Remove evaluated node from queue
        dfsStack.pop();

        // Add to list of visited nodes 
        nodeHistory.push_back(current);

        if (current.isFinish())
        {
            std::cout << "[Uniformed] DFS: Found Finish" 
                      << "\nNote: Speed of search has been slowed down by GUI display."
                      << std::endl;
            
            // Construct path & update GUI with path
            constructPath(nodeHistory);
            guiShowConstructedPath();
            
            guiClose();
            break;
        }

        // Add each valid edges node to the stack
        for (int i = 0; i < EDGE_AMOUNT; i++) {
            if (current.isValidEdge(i)) {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit())
                {
                    // Set the parent node for surrounding nodes
                    neighbor.setParent(current);
                    
                    // Add to queue and set flag
                    dfsStack.push(neighbor);
                    neighbor.setPendingVisit(true);
                    
                    // Update the GUI display
                    guiRefresh(neighbor);
                }
            }
        }
    }
}

void Search::cusDijk()
{
    searchMethod = "DIJK";
    generateMap();

    // Draw Window and wall
    guiOpen("VisX", 800, 600);
    guiShowWall();

    std::vector<Node> nodeHistory;
    std::priority_queue<Node&, std::vector<std::reference_wrapper<Node>>, lowestFScore> openSet;

    // Get starting point, add it to the queue and set as visited
    Coord start = getStartPos();
    Node &root = mapMaze[start.x][start.y];
    openSet.push(root);
    root.setVisitFlag(true);

    root.setGScore(0);

    while (!openSet.empty())
    {
        // Put the minimium fscore element to the front 
        std::make_heap(const_cast<std::reference_wrapper<Node>*>(&openSet.top()),
                       const_cast<std::reference_wrapper<Node>*>(&openSet.top()) + openSet.size(),
                       lowestFScore());

        Node &current = openSet.top();

        // Re-assign pending flag to visited
        current.setPendingVisit(false);
        current.setVisitFlag(true);

        // Update the GUI display
        guiRefresh(current);

        openSet.pop();

        // Add to list of visited nodes 
        nodeHistory.push_back(current);

        if (current.isFinish())
        {
            std::cout << "[Informed] Dijkstra: Found Finish"
                << "\nNote: Speed of search has been slowed down by GUI display."
                << std::endl;

            // Construct path & update GUI with path
            constructPath(nodeHistory);
            guiShowConstructedPath();

            guiClose();
            break;
        }

        // Add each valid edges node to the queue
        for (int i = 0; i < EDGE_AMOUNT; i++)
        {
            if (current.isValidEdge(i))
            {
                Node &neighbor = mapMaze[current.getEdge(i).x][current.getEdge(i).y];
                // If not a wall and has been visited, ignore
                if (neighbor.isNotWall() && !(neighbor.isNotVisited())) continue;

                // If not in openset, add it and set flag
                if (neighbor.isNotWall() && neighbor.isNotVisited() && neighbor.isNotPendingVisit())
                {
                    // Add to queue and set flag
                    openSet.push(neighbor);
                    neighbor.setPendingVisit(true);

                    // Update the GUI display
                    guiRefresh(neighbor);
                }

                // Calculate gScore, and see if it is better than neigbours current score.
                int tentativeGScore = current.getGScore() + MOVEMENT_COST;
                if (tentativeGScore >= neighbor.getGScore()) continue;

                // This path is the best until now. Record it!
                neighbor.setParent(current);
                neighbor.setGScore(tentativeGScore);
                int fScore = neighbor.getGScore();
                neighbor.setFScore(fScore);
            }
        }
    }
}

void Search::cus01()
{
    searchMethod = "NULL";
    std::cout << "[Uniformed] CUS01: This was never implemented!" << std::endl;
}

void Search::constructPath(std::vector<Node>& nodeTaken)
{
    Coord parent = getFinishPos();

    // Store each successful parent nodes from finish to start node.
    for (size_t i = (nodeTaken.size() - 1); i > 0 ; i-- )
    {
        // Check if this node is the parent of the previously checked node
        if ((nodeTaken[i].getX() == parent.x) && (nodeTaken[i].getY() == parent.y)) {
            path.push_back(nodeTaken[i]);

            // Store the current nodes parent
            parent.x = nodeTaken[i].getParentX();
            parent.y = nodeTaken[i].getParentY();
        }
        
    }
}






