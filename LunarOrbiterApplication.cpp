#include "LunarOrbiterApplication.h"
#include "LunarUIManager.h"
#include "LunarSurfaceLabelManager.h"

// Forge
#include "InputManager.h"
#include "GraphicsManager.h"
#include "MainWindow.h"
#include "Mesh.h"
#include "Cube.h"
#include "Icosphere.h"
#include "SkySphere.h"

using namespace Forge;

LunarOrbiterApplication::LunarOrbiterApplication(HINSTANCE hInstance, int nCMDShow) : Application(hInstance, nCMDShow)
{
	HWND hWnd = _mainWindow->GetHWND();

	// Setup UI
	_lunarUIManager = std::make_unique<LunarUIManager>();
	_lunarUIManager->Initialize(hWnd, _graphicsManager->GetDevice().Get(), _graphicsManager->GetDeviceContext().Get());

	// Setup Surface Labels
	_lunarSurfaceLabelManager = std::make_unique<LunarSurfaceLabelManager>();
	_lunarSurfaceLabelManager->LoadLabelsFromJSON(GetResourcePath("data/lunar_features.json").string());

	// setup Moon
	Icosphere moon(1.f, 8);
	moon.SetScale({ 3.f, 3.f, 3.f });
	moon.SetRotation({ 270.f, 90.f, 0.f });
	Texture moon_texture(GetResourcePath("images/moon_color_8k.jpg").string());
	Texture moon_displacement(GetResourcePath("images/moon_displacement.jpg").string());
	Material moon_mat;
	moon_mat.SetMainTexture(moon_texture);
	moon_mat.SetDisplacementMap(moon_displacement);
	moon_mat.SetDisplacementStrength(0.1f);
	moon.SetMaterial(moon_mat);

	// setup Sky
	SkySphere sky;
	Material sky_mat(false);
	Texture sky_texture(GetResourcePath("images/stars.png").string());
	sky_mat.SetMainTexture(sky_texture);
	sky.SetMaterial(sky_mat);
	sky.SetScale({ 50.f, 50.f, 50.f });
	sky.SetRotation({ 0.f, 90.f, 0.f });

	_meshes.push_back(moon);
	_meshes.push_back(sky);

	_scrollEventID = _inputManager->BindMouseScrollEvent(MouseEvent::ScrollVertical, [this](int delta) { OnMouseScroll(delta); });
	_mouseMoveEventID = _inputManager->BindMouseMoveEvent([this](MouseState state) { OnMouseMove(state); });
	_leftMouseClickEventID = _inputManager->BindMouseButtonEvent(MouseButton::Left, MouseEvent::ButtonDown, [this](MouseEvent event) { OnLeftMouseClicked(); });

	_currentCamera.SetPosition({ 0.f, -10.f, 0.f });
	_currentCamera.SetOrbitTargetPosition(moon.GetPosition());
	_currentCamera.SetOrbitTarget(true);
}

LunarOrbiterApplication::~LunarOrbiterApplication()
{
	_inputManager->UnBindMouseScrollEvent(_scrollEventID);
	_inputManager->UnBindMouseMoveEvent(_mouseMoveEventID);
	_inputManager->UnBindMouseButtonEvent(_leftMouseClickEventID);

	_lunarSurfaceLabelManager.release();
	_lunarUIManager->Shutdown();
	_lunarUIManager.release();
}

const LunarUIManager* LunarOrbiterApplication::GetLunarUIManager() const
{
	return _lunarUIManager.get();
}
void LunarOrbiterApplication::BeginFrame(float deltaTime)
{
	Application::BeginFrame(deltaTime);

	_lunarUIManager->DrawTitleWindow();
	_lunarSurfaceLabelManager->Update(_meshes[0].GetTransform());
	_lunarSurfaceLabelManager->Render();
	_lunarUIManager->DrawFeatureDescriptionWindow();
	_lunarUIManager->Render();
}

void LunarOrbiterApplication::OnMouseScroll(int delta)
{
	_currentCamera.Zoom(delta > 0 ? 1 : -1);
	_meshes[1].SetPosition(_currentCamera.GetPosition());
}
void LunarOrbiterApplication::OnMouseMove(MouseState state)
{
	if (_inputManager->IsMouseButtonDown(MouseButton::Left))
	{
		_currentCamera.Orbit(
			static_cast<float>(state.deltaX),
			static_cast<float>(state.deltaY)
		);

		_meshes[1].SetPosition(_currentCamera.GetPosition());
	}
}
void LunarOrbiterApplication::OnLeftMouseClicked()
{
	LunarSurfaceLabel* hoveredLabel = _lunarSurfaceLabelManager->GetHoveredLabel();
	if (hoveredLabel != nullptr)
	{
		_lunarUIManager->SetFeatureDescriptionLabel(hoveredLabel);
	}
}
