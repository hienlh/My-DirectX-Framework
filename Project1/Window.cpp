#include "Window.h"
#include "Macros.h"

using namespace Framework::Base;

// Internal Window Class
class CWindow_Internal final : public IWindow
{
private:
	static CWindow_Internal* __instance;

private:
	HWND m_hWnd;

private:
	CWindow_Internal() 
	{
		m_hWnd = nullptr;
	}
	~CWindow_Internal() {}

public:
	HWND Get_WindowHandle() override
	{
		return m_hWnd;
	}

private:
	bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
	{
		// Start initialization
		bool result = false;
		do
		{
			// create window class structure
			WNDCLASSEX wc;
			wc.cbSize = sizeof(WNDCLASSEX);

			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.hInstance = hInstance;
			wc.lpfnWndProc = static_cast<WNDPROC>(WinProc);
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hIcon = nullptr;
			wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
			wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = APP_TITLE;
			wc.hIconSm = nullptr;

			// register window class
			ATOM registerResult = RegisterClassEx(&wc);
			if (!registerResult)
			{
				OutputDebugString("[Error] RegisterClassExA failed\n");
				break;
			}

			// create window
			DWORD dwWindowStyle = (fullscreen
				? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP
				: WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST);

			m_hWnd = CreateWindow(
				APP_TITLE, APP_TITLE,         // window class | title bar
				dwWindowStyle,                // window style
				CW_USEDEFAULT, CW_USEDEFAULT, // x, y position of window
				screenWidth, screenHeight,    // width, height of the window
				NULL, NULL,                   // parent window | menu
				hInstance,                    // application instance
				NULL                          // window parameters
			);

			if (!m_hWnd)
			{
				OutputDebugStringA("[Error] CreateWindowA failed\n");
				break;
			}

			// show window
			ShowWindow(m_hWnd, nShowCmd);
			UpdateWindow(m_hWnd);

			result = true;
		} while (false);

		return result;
	}

public:
	static CWindow_Internal* Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen);
	static void Destroy();
};

CWindow_Internal* CWindow_Internal::__instance = nullptr;

CWindow_Internal * CWindow_Internal::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CWindow_Internal);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			SAFE_DELETE(__instance);
	}

	return __instance;
}

void CWindow_Internal::Destroy()
{
	SAFE_DELETE(__instance);
}

IWindow * IWindow::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	return CWindow_Internal::Instantiate(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen);
}

void IWindow::Destroy()
{
	CWindow_Internal::Destroy();
}
