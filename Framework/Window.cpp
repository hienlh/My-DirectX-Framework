#include "stdafx.h"

#include "Window.h"
#include "Macros.h"

using namespace Framework;

CWindow* CWindow::__instance = nullptr;

bool CWindow::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	// Start initialization
	bool result = false;
	do
	{
		// create window class structure
		WNDCLASSEXW wc;
		wc.cbSize = sizeof(WNDCLASSEXW);

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = hInstance;
		wc.lpfnWndProc = static_cast<WNDPROC>(WinProc);
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = nullptr;
		wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = APP_TITLE;
		wc.hIconSm = nullptr;

		// register window class
		ATOM registerResult = RegisterClassExW(&wc);
		if (!registerResult)
		{
			//OutputDebugStringW("[Error] RegisterClassExA failed\n");
			break;
		}

		// create window
		DWORD dwWindowStyle = (fullscreen
			? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP
			: WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST);

		m_hWnd = CreateWindowW(
			APP_TITLE, APP_TITLE,         // window class | title bar
			dwWindowStyle,                // window style
			CW_USEDEFAULT, CW_USEDEFAULT, // x, y m_position of window
			screenWidth + OVER_X, screenHeight + OVER_Y,    // width, height of the window
			NULL, NULL,                   // parent window | menu
			hInstance,                    // application instance
			NULL                          // window parameters
		);

		if (!m_hWnd)
			break;

		// show window
		ShowWindow(m_hWnd, nShowCmd);
		UpdateWindow(m_hWnd);

		result = true;
	} while (false);

	return result;
}

void CWindow::Release()
{
	DestroyWindow(m_hWnd);
}

void CWindow::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CWindow);

		if (!__instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
		{
			__instance->Release();
			SAFE_DELETE(__instance);
		}
	}
}

void CWindow::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CWindow* CWindow::GetInstance()
{
	return __instance;
}
