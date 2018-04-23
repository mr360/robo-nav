/*
Graphics.cpp
Date: 15/03/18
Author: 101119509
Description: Robotic Finder.
*/

#include "Graphics.h"

Graphics::Graphics()
{
    factory = NULL;
    renderTarget = NULL;
}

Graphics::~Graphics()
{
    if (factory) factory->Release();
    if (renderTarget) {
        brush->Release();
        renderTarget->Release();
    }
}

bool Graphics::Init(HWND gwHwnd)
{
    HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

    RECT rect;
    GetClientRect(gwHwnd, &rect);

    res = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            gwHwnd,
            D2D1::SizeU(rect.right, rect.bottom)),
        &renderTarget);

    if (res != S_OK) return false;
    return true;
}

void Graphics::DrawCell(int y, int x, int radius, float r, float g, float b, float a)
{
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
    renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y), radius, radius), brush, 10.0f);
}
