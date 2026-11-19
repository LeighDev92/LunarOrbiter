#pragma once
#include "framework.h"
#include "Texture.h"

namespace Forge
{

	class FORGE_API Material
	{
	public:
		Material(bool is_lit=true);

		FColor GetDiffuseColor() const;
		const Texture& GetMainTexture() const;
		const Texture& GetDisplacementMap() const;
		float GetDisplacementStrength() const;
		bool IsLit() const;

		void SetDiffuseColor(const FColor& color);
		void SetMainTexture(const Texture& tex);
		void SetDisplacementMap(const Texture& tex);
		void SetDisplacementStrength(float strength);

	private:
		FColor diffuseColor;
		Texture texture;
		Texture displacementMap;
		float displacementStrength;
		bool lit;
	};
}
