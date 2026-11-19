#pragma once

#include "framework.h"
using Microsoft::WRL::ComPtr;

namespace Forge
{
	class Mesh;
	class Camera;

	class FORGE_API GraphicsManager
	{
	public:
		GraphicsManager(HWND hWnd);
		GraphicsManager(const GraphicsManager&) = delete;
		GraphicsManager& operator=(const GraphicsManager&) = delete;
		~GraphicsManager();
		
		void Resize(UINT width, UINT height);

		void DrawMesh(Mesh* mesh, bool draw_solid=true, bool draw_wireframe=false);

		void SetCamera(Camera* camera);
		FVector2D ConvertToClipPosition(FVector world, FTransform transform);
		bool IsPositionOnSphereVisibleToCamera(FVector position, FTransform transform) const;

		void PresentFrame();

		void ClearScreen(float red, float green, float blue) noexcept;
		void ClearRenderTargetView(float red, float green, float blue) noexcept;
		void ClearDepthStencilView() noexcept;

		const ComPtr<ID3D11Device> GetDevice() const;
		const ComPtr<ID3D11DeviceContext> GetDeviceContext() const;

		bool CreateTextureFromFile(ComPtr<ID3D11ShaderResourceView>& texture, const char* filename);

	private:

		void CreateDeviceAndSwapChain(HWND hWnd);
		void CreateRenderTargets();
		void CreateShaders();
		void CreateInputLayouts();
		void CreateRasterizerStates();
		void CreateDepthStencilStates();
		void CreateSamplers();
		void CreateConstantBuffers();

#ifdef _DEBUG
		ComPtr<ID3D11Debug> _debug;
#endif
		ComPtr<ID3D11Device> _device;
		ComPtr<IDXGISwapChain> _swapChain;
		ComPtr<ID3D11DeviceContext> _deviceContext;
		ComPtr<ID3D11RenderTargetView> _renderTargetView;
		ComPtr<ID3D11DepthStencilView> _depthStencilView;
		ComPtr<ID3D11DepthStencilState> _depthStencilState;
		ComPtr<ID3D11VertexShader> _vertexShader;
		ComPtr<ID3D11PixelShader> _pixelShader;
		ComPtr<ID3D11PixelShader> _wireframePixelShader;
		ComPtr<ID3D11InputLayout> _inputLayout;
		ComPtr<ID3D11RasterizerState> _solidRasterizerState;
		ComPtr<ID3D11RasterizerState> _wireframeRasterizerState;
		ComPtr<ID3D11SamplerState> _textureSamplerState;
		ComPtr<ID3D11Buffer> _modelConstantBuffer;
		ComPtr<ID3D11Buffer> _materialConstantBuffer;
		ComPtr<ID3D11Buffer> _lightingConstantBuffer;

		Camera* _camera;
	};
}