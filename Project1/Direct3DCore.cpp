#include "Direct3DCore.h"

using namespace Framework::Direct3DCore;


// Internal Direct3D Core Class
class CDirect3DCore_Internal final : public IDirect3DCore
{
	// Properties
private:
	HWND m_hWnd;

	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_d3ddev;
	LPDIRECT3DSURFACE9 m_backbuffer;
	LPD3DXSPRITE m_spriteHandler;

	// Cons/Des
public:
	CDirect3DCore_Internal()
	{
		m_hWnd = {};
		m_d3d = nullptr;
		m_d3ddev = nullptr;
		m_backbuffer = nullptr;
		m_spriteHandler = nullptr;
	}

	~CDirect3DCore_Internal()
	{
		if (m_d3d)
			m_d3d->Release();

		if (m_d3ddev)
			m_d3ddev->Release();

		if (m_backbuffer)
			m_backbuffer->Release();

		if (m_spriteHandler)
			m_spriteHandler->Release();
	}

	// Getters
public:
	LPDIRECT3D9 Get_Direct3D() const { return this->m_d3d; }
	LPDIRECT3DDEVICE9 Get_Direct3DDevice() const { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 Get_BackBuffer() const { return this->m_backbuffer; }
	LPD3DXSPRITE Get_SpriteHandler() const { return m_spriteHandler; }

	// Override methods
public:
	bool Init(HINSTANCE hInstance, int nShowCmd,
	                 int screenWidth, int screenHeight,
	                 bool fullscreen) override
	{
		bool result = false;
		do
		{
			if (!WindowInit(hInstance, nShowCmd, screenWidth, screenHeight, fullscreen))
			{
				OutputDebugStringA("[ERROR] WindowInit failed\n");
				break;
			}

			if (!Direct3DInit(fullscreen))
			{
				OutputDebugStringA("[ERROR] Direct3DInit failed\n");
				break;
			}

			result = true;
		}
		while (false);

		return result;
	}

	void Destroy() override
	{
		SAFE_DELETE(__instance);
	}

	bool Render() override
	{
		bool result = false;
		do
		{
			// Start rendering
			if (m_d3ddev->BeginScene())
			{
				// Clear back buffer with black color
				m_d3ddev->ColorFill(m_backbuffer, nullptr, D3DCOLOR_XRGB(0, 0, 0));

				m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
				//m_pPlayer->Render(m_pDirect3D);
				m_spriteHandler->End();

				// stop rendering
				m_d3ddev->EndScene();
			}

			// display back buffer content to the screen
			m_d3ddev->Present(nullptr, nullptr, nullptr, nullptr);

			result = true;
		} while (false);

		return result;
	}

	// Internal methods
private:
	bool WindowInit(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight, bool fullscreen)
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
			wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
			wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = APP_TITLE;
			wc.hIconSm = nullptr;

			// register window class
			ATOM registerResult = RegisterClassExA(&wc);
			if (!registerResult)
			{
				OutputDebugStringA("[Error] RegisterClassExA failed\n");
				break;
			}

			// create window
			DWORD dwWindowStyle = (fullscreen
				                       ? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP
				                       : WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST);

			m_hWnd = CreateWindowA(
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
		}
		while (false);

		return result;
	}

	bool Direct3DInit(bool fullscreen)
	{
		bool result = false;
		do
		{
			// initialize Direct3D
			m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
			if (!m_d3d)
			{
				OutputDebugStringA("[Error] Direct3DCreate9 failed\n");
				break;
			}

			// set Direct3D presentation parameters
			D3DPRESENT_PARAMETERS d3dpp;

			ZeroMemory(&d3dpp, sizeof(d3dpp));

			d3dpp.Windowed = !fullscreen;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
			d3dpp.BackBufferCount = 1;

			RECT rect;
			GetClientRect(m_hWnd, &rect); // retrieve Window width & height 

			d3dpp.BackBufferWidth = rect.right + 1;
			d3dpp.BackBufferHeight = rect.bottom + 1;
			d3dpp.hDeviceWindow = m_hWnd;

			// create Direct3D device
			m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
			                    D3DDEVTYPE_HAL,
			                    m_hWnd,
			                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			                    &d3dpp,
			                    &m_d3ddev);

			if (!m_d3ddev)
			{
				OutputDebugStringA("[Error] CreateDevice failed\n");
				break;
			}

			// clear the back buffer to black
			m_d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

			// create pointer to the back buffer
			m_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer);
			if (!m_backbuffer)
			{
				OutputDebugStringA("[ERROR] GetBackBuffer failed\n");
				break;
			}

			// Initialize sprite helper from Direct3DX helper library
			D3DXCreateSprite(m_d3ddev, &m_spriteHandler);
			if (!m_spriteHandler)
			{
				OutputDebugStringA("[ERROR] D3DXCreateSprite failed\n");
				break;
			}

			result = true;
		}
		while (false);

		return result;
	}

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture)
	{
		D3DXVECTOR3 position(x, y, 0);
		m_spriteHandler->Draw(texture, nullptr, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
	}
};

// Direct3D Core Initialization
IDirect3DCore* IDirect3DCore::__instance = nullptr;

IDirect3DCore* IDirect3DCore::GetInstance()
{
	SAFE_ALLOC(__instance, CDirect3DCore_Internal);
	return __instance;
}
