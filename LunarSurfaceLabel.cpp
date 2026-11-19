#include "LunarSurfaceLabel.h"

namespace
{
	const double PI = std::acos(-1.0);
}

LunarSurfaceLabel::LunarSurfaceLabel(LunarSurfaceLabelData label_data, bool visible)
{
	_data = label_data;
	_visiblity = visible;
}

LunarSurfaceLabelData LunarSurfaceLabel::GetSurfaceLabelData() const
{
	return _data;
}

std::string LunarSurfaceLabel::GetName() const
{
	return _data.name;
}

std::string LunarSurfaceLabel::GetType() const
{
	return _data.type;
}

std::string LunarSurfaceLabel::GetDescription() const
{
	return _data.description;
}

float LunarSurfaceLabel::GetLatitude() const
{
	return _data.latitude;
}

float LunarSurfaceLabel::GetLongitude() const
{
	return _data.longitude;
}

float LunarSurfaceLabel::GetDiameter() const
{
	return _data.diameterKm;
}

const Forge::Texture* LunarSurfaceLabel::GetImageTexture() const
{
	return _imageTexture.get();
}

Forge::FVector LunarSurfaceLabel::GetPosition(float radius) const
{

	// Convert degrees to radians
	float lat = _data.latitude * PI / 180.f;
	float lon = _data.longitude * PI / 180.f;

	// Calculate Position based on latitude, longitude
	float cosLat = cosf(lat);
	float x = radius * cosLat * cosf(lon);
	float y = -radius * cosLat * sinf(lon);
	float z = radius * sinf(lat);

	return Forge::FVector(x, y, z);
}

Forge::FVector2D LunarSurfaceLabel::GetScreenPosition() const
{
	return _screenPosition;
}

bool LunarSurfaceLabel::GetVisibility() const
{
	return _visiblity;
}

void LunarSurfaceLabel::SetScreenPosition(Forge::FVector2D pos)
{
	_screenPosition = pos;
}

void LunarSurfaceLabel::SetVisibility(bool visible)
{
	_visiblity = visible;
}

bool LunarSurfaceLabel::LoadImage()
{
	if (_imageTexture && _imageTexture->IsValidTexture())
	{
		return false;
	}

	if (!_imageTexture)
	{
		_imageTexture = std::make_shared<Forge::Texture>();
	}

	std::string image_file = _data.image.filename;

	if (image_file == "")
	{
		image_file = "moon_general.jpg";
	}

	return _imageTexture->LoadTextureFromFile(GetResourcePath(image_file).string());
}
