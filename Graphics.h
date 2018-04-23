/*
Graphics.h
Date: 15/03/18
Author: 101119509
Description: Robotic Finder.
*/

#pragma once
#include <d2d1.h>

class Graphics
{
    private:
        ID2D1Factory* factory;
        ID2D1HwndRenderTarget* renderTarget;
        ID2D1SolidColorBrush* brush;
    
    public:
        Graphics();
        ~Graphics();

        bool Init(HWND windowHandle);

        void BeginDraw() { renderTarget->BeginDraw(); }
        void EndDraw() { renderTarget->EndDraw(); }

        void DrawCell(int y, int x, int radius, float r, float g, float b, float a);
};
