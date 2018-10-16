#pragma once
#include "Header.h"

namespace Framework
{
	// Window Interface
	class CWindow final
	{
		//Properties
	private:
		HWND m_hWnd = nullptr;

		// Cons / Des
	private:
		CWindow() = default;

	public:
		virtual ~CWindow() = default;

		//Private method
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);

		// Getters / Setters
	public:

		HWND Get_WindowHandle() { return m_hWnd;  }

		// Pattern
	public:
		static CWindow* Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
	};
}
