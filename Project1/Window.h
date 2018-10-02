#pragma once
#include "Header.h"

namespace Framework
{
	namespace Base
	{
		// Window Interface
		class IWindow
		{
			// Cons / Des
		protected:
			IWindow() = default;
			virtual ~IWindow() = default;

			// Getters / Setters
		public:
			virtual HWND Get_WindowHandle() = 0;

			// Pattern
		public:
			static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
			static void Release();
			static IWindow* GetInstance();
		};
	}
}
