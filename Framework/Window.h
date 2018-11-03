#pragma once

namespace Framework
{
	// Window Interface
	class CWindow final
	{
		// Used for singleton pattern
	private:
		static CWindow* __instance;

		// Cons / Des
	private:
		CWindow() = default;
		~CWindow() = default;

		// Properties
	private:
		HWND m_hWnd = nullptr;

		// Getters / Setters
	public:
		HWND Get_WindowHandle() { return m_hWnd; };

		// Internal methods
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		void Release();

		// Static methods
	public:
		static void Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy();
		static CWindow* GetInstance();
	};
}