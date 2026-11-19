#pragma once
#include "framework.h"
#include "LunarSurfaceLabel.h"

class LunarSurfaceLabelManager
{
public:
    LunarSurfaceLabelManager(float rad = 1.f);

    LunarSurfaceLabel* GetHoveredLabel() const;

    void LoadLabelsFromJSON(const std::string& filename);
    void SetRadius(float rad);
    void Update(Forge::FTransform transform);
    void Render();

private:
    bool IsMouseOverLabel(const LunarSurfaceLabel& label);

    std::vector<LunarSurfaceLabel> _labels;
    float _radius;
    LunarSurfaceLabel* _hoveredLabel;
};