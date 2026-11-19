#pragma once
#include "framework.h"

class LunarSurfaceLabel;

class LunarUIManager
{
public:
    bool Initialize(HWND hwnd, ID3D11Device* device,
        ID3D11DeviceContext* context);

    void Shutdown();

    void DrawTitleWindow();
    void DrawFeatureDescriptionWindow();
    void Render();

    void SetFeatureDescriptionLabel(LunarSurfaceLabel* data);

private:
    LunarSurfaceLabel* _selectedLabel;
};