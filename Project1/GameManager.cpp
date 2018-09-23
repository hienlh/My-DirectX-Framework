#include "GameManager.h"

CGameManager* CGameManager::m_instance = nullptr;

bool CGameManager::Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight)
{
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
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = APP_TITLE;
		wc.hIconSm = nullptr;

		// register window class
		ATOM registerResult = RegisterClassEx(&wc);
		if (!registerResult)
		{
			OutputDebugString("[Error] RegisterClassEx failed\n");
			break;
		}

		// create window
		DWORD dwWindowStyle = (m_fullscreen == TRUE
			                       ? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP
			                       : WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST);
		m_hWnd = CreateWindow(
			APP_TITLE, APP_TITLE,         // window class | title bar
			dwWindowStyle,                // window style
			CW_USEDEFAULT, CW_USEDEFAULT, // x, y position of window
			SCREEN_WIDTH, SCREEN_HEIGHT,  // width, height of the window
			NULL, NULL,                   // parent window | menu
			hInstance,                    // application instance
			NULL                          // window parameters
		);

		if (!m_hWnd)
		{
			OutputDebugString("[Error] CreateWindow failed\n");
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
			OutputDebugString("[Error] CDirect3D::Init failed\n");
			break;
		}

		result = true;
	}
	while (false);

	return result;
}

void CGameManager::LoadResources()
{
	CreatePlayer();
}

bool CGameManager::Render() const
{
	bool result = false;
	do
	{
		LPDIRECT3DDEVICE9 d3ddev = m_pDirect3D->Get_Direct3DDevice();
		// make sure the Direct3D device is valid
		if (!d3ddev)
		{
			OutputDebugString("[Error] GetDirect3DDevice failed\n");
			break;
		}

		LPDIRECT3DSURFACE9 backbuffer = m_pDirect3D->Get_BackBuffer();
		// make sure the back buffer is valid
		if (!backbuffer)
		{
			OutputDebugString("[Error] GetBackBuffer failed\n");
			break;
		}

		// Start rendering
		if (d3ddev->BeginScene())
		{
			// Clear back buffer with black color
			d3ddev->ColorFill(backbuffer, nullptr, D3DCOLOR_XRGB(0, 0, 0));

			m_pDirect3D->Get_SpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
			m_pPlayer->Render(m_pDirect3D);
			m_pDirect3D->Get_SpriteHandler()->End();


			// stop rendering
			d3ddev->EndScene();
		}

		// display back buffer content to the screen
		d3ddev->Present(nullptr, nullptr, nullptr, nullptr);

		result = true;
	}
	while (false);

	return result;
}

void CGameManager::Run()
{
	DWORD frameStart = GetTickCount();
	const DWORD tickPerFrame = 1000 / FRAME_RATE;

	bool done = false;
	while (!done)
	{
		if (PeekMessage(&m_message, nullptr, 0, 0, PM_REMOVE))
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
				OutputDebugString("[Error] CGame::Render failed\n");
				break;
			}
		}
		else
			Sleep(tickPerFrame - dt);
	}
}

bool CGameManager::CreatePlayer()
{
	m_pPlayer = new CGameObject();
	m_pPlayer->Set_Texture(m_pDirect3D->Get_Direct3DDevice(), TANK_PATH);
	m_pPlayer->SetPosition(10.0f, 130.0f);

	return true;
}