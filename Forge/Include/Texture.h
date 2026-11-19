#pragma once
#include "framework.h"

namespace Forge
{
	class FORGE_API Texture
	{
	public:
		Texture(std::string filename = "");
		bool LoadTextureFromFile(std::string filename);
		bool LoadImageFromURL(std::string url);

		bool IsValidTexture() const;

		const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResource() const;

	private:

		bool loaded;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _textureView;
	};
}
