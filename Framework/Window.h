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
		const HWND& Get_WindowHandle() const { return m_hWnd; };

		// Internal methods
	private:
		bool Init(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth, const int& screenHeight,
		          const bool& fullscreen);
		void Release();

		// Pattern
	public:
		static CWindow* Instantiate(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth,
		                            const int& screenHeight, const bool& fullscreen);
		static void Destroy(CWindow* instance);
	};
}