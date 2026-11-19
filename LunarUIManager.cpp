#include "LunarUIManager.h"
#include "LunarSurfaceLabel.h"

bool LunarUIManager::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Create ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Configure ImGui
    ImGui::StyleColorsDark();

    // Initialize platform and renderer backends
    if (!ImGui_ImplWin32_Init(hwnd))
        return false;

    if (!ImGui_ImplDX11_Init(device, context))
        return false;

    return true;
}

void LunarUIManager::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void LunarUIManager::DrawTitleWindow()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(50, 50));
    ImGui::SetNextWindowSize(ImVec2(400, 200));
    ImGui::Begin("Lunar Orbiter");
    ImGui::Text("Explore the Moon, navigate its surface,and\ndiscover notable geographic features such as \ncraters, maria, mountains, and Apollo landing sites.");
    ImGui::End();
}

void LunarUIManager::DrawFeatureDescriptionWindow()
{
    if (_selectedLabel == nullptr)
    {
        return;
    }

    const LunarSurfaceLabelData& data = _selectedLabel->GetSurfaceLabelData();

    ImGui::SetNextWindowPos(ImVec2(50, 300));
    ImGui::SetNextWindowSize(ImVec2(400, 600));
    ImGui::Begin(data.name.c_str());
    ImGui::Separator();
    ImGui::TextWrapped("%s", data.description.c_str());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Latitude: %.2f", data.latitude);
    ImGui::Text("Longitude: %.2f", data.longitude);
    ImGui::Text("Diameter: %.2f km", data.diameterKm);
    ImGui::Text("Type: %s", data.type.c_str());
    ImGui::Spacing();
    ImGui::Separator();

    const Forge::Texture* image = _selectedLabel->GetImageTexture();
    if (image && image->IsValidTexture())
    {
        ImGui::Image(
            (ImTextureID)image->GetShaderResource().Get(),
            ImVec2(385.0f, 385.0f)
        );
    }

    ImGui::End();
}

void LunarUIManager::Render()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void LunarUIManager::SetFeatureDescriptionLabel(LunarSurfaceLabel* label)
{
    if (label == nullptr)
    {
        return;
    }

    _selectedLabel = label;
    _selectedLabel->LoadImage();
}
