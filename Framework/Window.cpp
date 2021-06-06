#include "stdafx.h"

#include "Window.h"
#include "Macros.h"

using namespace Framework;

LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}

	return result;
}

bool CWindow::Init(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth, const int& screenHeight,
	const bool& fullscreen)
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

CWindow* CWindow::Instantiate(const HINSTANCE& hInstance, const int& nShowCmd, const int& screenWidth,
	const int& screenHeight, const bool& fullscreen)
{
	CWindow* instance = nullptr;
	SAFE_ALLOC(instance, CWindow);

	if (!instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
		SAFE_DELETE(instance);

	return instance;
}

void CWindow::Destroy(CWindow* instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}