#pragma once
#include "framework.h"
#include "resource.h"
#include "Camera.h"

namespace Forge
{
	static const int MAX_LOADSTRING = 100;

	using BindingID = uint64_t;
	struct MouseState;

	class InputManager;
	class GraphicsManager;
	class MainWindow;
	class Mesh;

	class FORGE_API Application
	{
	public:
		static Application* Get();

		Application(HINSTANCE hInstance, int nCMDShow);
		~Application();

		int Run();

		virtual void BeginFrame(float deltaTime);
		virtual void EndFrame(float deltaTime);

		InputManager* GetInputManager() const;
		GraphicsManager* GetGraphicsManager() const;
		Camera* GetCamera();
		int AddMesh(Mesh* mesh);
		void RemoveMesh(Mesh* mesh);

		RECT GetMainWindowViewport();

		HINSTANCE GetHInstance() const;
		int GetCMDShow() const;
		HACCEL GetAcceleratorTable() const;
		LPCWSTR GetTitle() const;
		LPCWSTR GetAuthor() const;
		LPCWSTR GetMainWindowClass() const;

	protected:
		static Application* _instance;
		
		std::unique_ptr<MainWindow> _mainWindow;
		std::unique_ptr<InputManager> _inputManager;							
		std::unique_ptr<GraphicsManager> _graphicsManager;

		std::vector<Mesh> _meshes;											// collection of meshes

		Camera _currentCamera;												// Camera used for rendering

		HINSTANCE _hInstance;												// Window Instance handle    
		int _nCMDShow;														// WinMain Show Options

		WCHAR _szTitle[MAX_LOADSTRING];										// The title bar text
		WCHAR _szAuthor[MAX_LOADSTRING];									// The author of this program
		WCHAR _szWindowClass[MAX_LOADSTRING];								// The main window class name

		HACCEL _hAccelTable;												// Handle to the Accelerator Table

		std::chrono::steady_clock::time_point _applicationStartTime;		// Application start time
		std::chrono::steady_clock::time_point _lastFrameTime;				// Time since last frame
	};
}
