#pragma once

namespace Framework
{
	// Window Interface
	class CWindow final
	{
		// Properties
	private:
		HWND m_hWnd = nullptr;

		// Cons / Des
	private:
		CWindow() = default;
		~CWindow() = default;

		// Getters / Setters
	public:
		HWND Get_WindowHandle() const { return m_hWnd; };

		// Internal methods
	private:
		bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		void Release();

		// Pattern
	public:
		static CWindow* Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
		static void Destroy(CWindow* instance);
	};
}