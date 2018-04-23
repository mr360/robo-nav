/*
Search.h
Date: 15/03/18
Author: 101119509
Description: [Add Details]
*/

#pragma once

#include <vector>
#include "Node.h"  
#include <windows.h>
#include "Graphics.h"

class Search
{
private:
    std::vector<std::vector<Node>> mapMaze;
    std::vector<int> mapList;           // Store the parsed txt file
    std::vector<Node> path;
    std::string searchMethod;

    // Gui variables and functions
    Graphics* graphics;              // DirectX2d graphics 
    int     guiWidth, guiHeight;    // Size of drawing area
    HWND    guiHwnd = NULL;        // Handle to window

    void guiDraw(Node& cell);     // Draws up the node based on its characteristics (e.g isWall)
    static LRESULT CALLBACK guiWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  // Win32 event handler (redraw to be sent to window)

public:
    Search();
    ~Search();
    friend std::istream& operator >> (std::istream& aIStream, Search& aObject);
    friend std::ostream& operator << (std::ostream& aOStream, Search& aObject);

    // Getter and map generater methods
    void generateMap();
    Coord getDimension();
    Coord getStartPos();
    Coord getFinishPos();

    // Search Algorithms
    void bfs();
    void dfs();
    void aStar();
    void gbfs();
    void cusDijk();
    void cus01();

    // Path reconstruction
    void constructPath(std::vector<Node>& nodeTaken);

    // GUI
    void guiOpen(LPSTR title, int width, int height);
    void guiClose();
    void guiRefresh(Node& cell);
    void guiShowWall();
    void guiShowConstructedPath();
    
};