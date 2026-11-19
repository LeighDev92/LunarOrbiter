#pragma once
#include "framework.h"

namespace Forge
{
	class FORGE_API Window
	{
	public:
		Window();
		~Window();

		virtual ATOM Register();
		virtual BOOL Create();
		BOOL Show() const;
		BOOL Update() const;

		HWND GetHWND();

		virtual LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:

		static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
		static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:

		static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

		HWND _hWnd;
	};
}
