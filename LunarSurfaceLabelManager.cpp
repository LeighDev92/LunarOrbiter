#include "LunarSurfaceLabelManager.h"
#include "LunarSurfaceLabel.h"

// Forge
#include "Application.h"
#include "GraphicsManager.h"
#include "nlohmann/json.hpp"
using nlohmann::json;

LunarSurfaceLabelManager::LunarSurfaceLabelManager(float rad)
{
    _radius = rad;
    _hoveredLabel = nullptr;
}

LunarSurfaceLabel* LunarSurfaceLabelManager::GetHoveredLabel() const
{
    return _hoveredLabel;
}

void LunarSurfaceLabelManager::LoadLabelsFromJSON(const std::string& filename)
{
    _labels.clear();

    std::ifstream file(filename);

    if (!file.is_open())
    {
        OutputDebugStringA(("Failed to open lunar feature file: " + filename).c_str());
    }

    try
    {
        json data;
        file >> data;

        // parse each label from json file
        for (auto& [category, features] : data.items())
        {
            if (!features.is_array())
                continue;

            for (const auto& feature : features)
            {
                LunarSurfaceLabelData labelData;

                labelData.name = feature.value("name", "");
                labelData.description = feature.value("description", "");
                labelData.latitude = static_cast<float>(feature.value("latitude", 0.0));
                labelData.longitude = static_cast<float>(feature.value("longitude", 0.0));
                labelData.diameterKm = static_cast<float>(feature.value("diameter_km", 0.0));
                labelData.type = feature.value("type", "");
                labelData.priority = static_cast<float>(feature.value("priority", 1));

                const auto& image = feature["image"];
                labelData.image.filename = image.value("filename", "");
                labelData.image.alt = image.value("alt", "");
                labelData.image.credit = image.value("credit", "");

                _labels.emplace_back(labelData);
            }
        }
    }
    catch (const json::exception& e)
    {
        OutputDebugStringA(("JSON parsing error: " + std::string(e.what())).c_str());
    }
}

void LunarSurfaceLabelManager::SetRadius(float rad)
{
    _radius = abs(rad);
}

void LunarSurfaceLabelManager::Update(Forge::FTransform transform)
{
    Forge::GraphicsManager* graphicsManager = Forge::Application::Get()->GetGraphicsManager();

    // update visibility of labels
    for (LunarSurfaceLabel& label : _labels)
    {
        Forge::FVector localPosition = label.GetPosition(_radius);

        // Convert to Screen Positions
        label.SetScreenPosition(graphicsManager->ConvertToClipPosition(localPosition, transform));

        // Cull if positon is not visible to camera
        bool visible = graphicsManager->IsPositionOnSphereVisibleToCamera(localPosition, transform);
      
        // Cull based on distance from moon and label priority
        Forge::Camera* camera = Forge::Application::Get()->GetCamera();
        if (camera != nullptr)
        {
            float cameraZoom = camera->GetOrbitDistance();
            if (15 - cameraZoom < label.GetSurfaceLabelData().priority && label.GetSurfaceLabelData().priority != 1)
            {
                visible = false;
            }
        }

        label.SetVisibility(visible);
    }
}

void LunarSurfaceLabelManager::Render()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings;

    if (ImGui::Begin("SurfaceLabelOverlay", nullptr, flags))
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        _hoveredLabel = nullptr;

        // draw each label on screen
        for (int i = 0; i < _labels.size(); i++)
        {
            LunarSurfaceLabel& label = _labels[i];

            // do not draw if not visible
            if (!label.GetVisibility())
                continue;

            Forge::FVector2D pos = label.GetScreenPosition();
            const std::string& name = label.GetName();
            ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
            ImVec2 rectPos(pos.X - 3.f, pos.Y - 3.f);
            ImVec2 rectSize(textSize.x + 6.f, textSize.y + 6.f);

            ImGui::PushID(i);

            // determine if currently hovering over this label
            bool hovered = IsMouseOverLabel(label) && _hoveredLabel == nullptr;

            if (hovered)
            {
                drawList->AddRect(
                    rectPos,
                    ImVec2(
                        rectPos.x + rectSize.x,
                        rectPos.y + rectSize.y
                    ),
                    IM_COL32(0, 255, 0, 255)
                );

                _hoveredLabel = &label;
            }

            drawList->AddText(
                ImVec2(pos.X, pos.Y),
                hovered
                ? IM_COL32(255, 220, 0, 255)
                : IM_COL32(255, 255, 255, 255),
                name.c_str()
            );

            ImGui::PopID();
        }
    }

    ImGui::End();
}

bool LunarSurfaceLabelManager::IsMouseOverLabel(const LunarSurfaceLabel& label)
{
    ImVec2 mousePosition = ImGui::GetIO().MousePos;
    Forge::FVector2D pos = label.GetScreenPosition();

    ImVec2 textSize = ImGui::CalcTextSize(
        label.GetName().c_str()
    );

    const float padding = 4.f;

    ImVec2 min(
        pos.X - padding,
        pos.Y - padding
    );

    ImVec2 max(
        pos.X + textSize.x + padding,
        pos.Y + textSize.y + padding
    );

    return mousePosition.x >= min.x &&
        mousePosition.x <= max.x &&
        mousePosition.y >= min.y &&
        mousePosition.y <= max.y;
}