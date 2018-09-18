#include "CGame.h"

CGame* CGame::m_instance = nullptr;

bool CGame::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight)
{
	bool result = false;
	do
	{
		// create window class structure
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = hInstance;
		wc.lpfnWndProc = (WNDPROC)WinProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = APP_TITLE;
		wc.hIconSm = NULL;

		// register window class
		ATOM registerResult = RegisterClassEx(&wc);
		if (!registerResult)
		{
			MessageBox(m_hWnd, "[Error] RegisterClassEx failed", "Error", MB_OK);
			break;
		}

		// create window
		DWORD dwWindowStyle = (FULL_SCREEN == TRUE ? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP : WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST);
		m_hWnd = CreateWindow(
			APP_TITLE, APP_TITLE,			// window class | title bar
			dwWindowStyle,					// window style
			CW_USEDEFAULT, CW_USEDEFAULT,	// x, y position of window
			SCREEN_WIDTH, SCREEN_HEIGHT,	// width, height of the window
			NULL, NULL,						// parent window | menu
			hInstance,						// application instance
			NULL							// window parameters
		);

		if (!m_hWnd)
		{
			MessageBox(m_hWnd, "[Error] CreateWindow failed", "Error", MB_OK);
			break;
		}

		// show window
		ShowWindow(m_hWnd, nShowCmd);
		UpdateWindow(m_hWnd);

		// init Direct3D
		m_pDirect3D = CDirect3D::GetInstance();

		bool initResult = m_pDirect3D->Init(m_hWnd, FULL_SCREEN);
		if (!initResult)
		{
			MessageBox(m_hWnd, "[Error] CDirect3D::Init failed", "Error", MB_OK);
			break;
		}

		result = true;
	} while (false);

	return result;
}

bool CGame::Render()
{
	bool result = false;
	do
	{
		LPDIRECT3DDEVICE9 d3ddev = m_pDirect3D->Get_Direct3DDevice();
		// make sure the Direct3D device is valid
		if (!d3ddev)
		{
			MessageBox(m_hWnd, "[Error] GetDirect3DDevice failed", "Error", MB_OK);
			break;
		}

		LPDIRECT3DSURFACE9 backbuffer = m_pDirect3D->Get_BackBuffer();
		// make sure the back buffer is valid
		if (!backbuffer)
		{
			MessageBox(m_hWnd, "[Error] GetBackBuffer failed", "Error", MB_OK);
			break;
		}

		// Start rendering
		if (d3ddev->BeginScene())
		{
			// Clear back buffer with black color
			d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));

			// stop rendering
			d3ddev->EndScene();
		}

		// display back buffer content to the screen
		d3ddev->Present(NULL, NULL, NULL, NULL);

		result = true;
	} while (false);
	
	return result;
}

void CGame::Run()
{
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;

	bool done = false;
	while (!done)
	{
		if (PeekMessage(&m_message, NULL, 0, 0, PM_REMOVE))
		{
			// check for escape key (to exit program)
			if (m_message.message == WM_QUIT)
				done = true;

			// translate message and send back to WinProc
			TranslateMessage(&m_message);
			DispatchMessage(&m_message);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			// process game loop
			bool renderResult = Render();
			if (!renderResult)
			{
				MessageBox(m_hWnd, "[Error] CGame::Render failed", "Error", MB_OK);
				break;
			}
		}
		else
			Sleep(tickPerFrame - dt);
	}
}