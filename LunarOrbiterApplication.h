#pragma once

#include "Application.h"

class LunarUIManager;
class LunarSurfaceLabelManager;

class LunarOrbiterApplication : public Forge::Application
{


public:
	LunarOrbiterApplication(HINSTANCE hInstance, int nCMDShow);
	~LunarOrbiterApplication();

	const LunarUIManager* GetLunarUIManager() const;

	virtual void BeginFrame(float deltaTime) override;
private:
	void OnMouseScroll(int delta);
	void OnMouseMove(Forge::MouseState state);
	void OnLeftMouseClicked();

	std::unique_ptr<LunarUIManager> _lunarUIManager;
	std::unique_ptr<LunarSurfaceLabelManager> _lunarSurfaceLabelManager;

	Forge::BindingID _scrollEventID;
	Forge::BindingID _mouseMoveEventID;
	Forge::BindingID _leftMouseClickEventID;
};