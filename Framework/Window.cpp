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

bool CWindow::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
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
			CW_USEDEFAULT, CW_USEDEFAULT, // x, y m_position of window
			screenWidth + OVER_X, screenHeight + OVER_Y,    // width, height of the window
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

CWindow* CWindow::Instantiate(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
{
	CWindow* instance = nullptr;
	SAFE_ALLOC(instance, CWindow);

	if (!instance->Init(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
		SAFE_DELETE(instance);

	return instance;
}