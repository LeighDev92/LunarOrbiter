#pragma once
#include "framework.h"
#include "Texture.h"

struct LunarSurfaceImageData
{
	std::string filename;
	std::string alt;
	std::string credit;
};

struct LunarSurfaceLabelData
{
	std::string name;
	std::string type;
	std::string description;

	float latitude = 0.0f;
	float longitude = 0.0f;
	float diameterKm = 0.0f;

	int priority = 1;

	LunarSurfaceImageData image;
};

class LunarSurfaceLabel
{
public:
	LunarSurfaceLabel(LunarSurfaceLabelData label_data = {}, bool visible = true);

	LunarSurfaceLabelData GetSurfaceLabelData() const;
	std::string GetName() const;
	std::string GetType() const;
	std::string GetDescription() const;
	float GetLatitude() const;
	float GetLongitude() const;
	float GetDiameter() const;
	const Forge::Texture* GetImageTexture() const;

	Forge::FVector GetPosition(float radius) const;
	Forge::FVector2D GetScreenPosition() const;

	bool GetVisibility() const;

	void SetScreenPosition(Forge::FVector2D pos);
	void SetVisibility(bool enabled);

	bool LoadImage();

private:
	LunarSurfaceLabelData _data;
	bool _visiblity;
	Forge::FVector2D _screenPosition;
	std::shared_ptr<Forge::Texture> _imageTexture;
};
