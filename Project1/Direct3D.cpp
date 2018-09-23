#include "Direct3D.h"

CDirect3D* CDirect3D::m_instance = nullptr;

bool CDirect3D::Init(HWND hWnd, bool fullscreen)
{
	bool result = false;
	do
	{
		// initialize Direct3D
		m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!m_d3d)
		{
			OutputDebugString("[Error] Direct3DCreate9 failed\n");
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
		GetClientRect(hWnd, &rect); // retrieve Window width & height 

		d3dpp.BackBufferWidth = rect.right + 1;
		d3dpp.BackBufferHeight = rect.bottom + 1;
		d3dpp.hDeviceWindow = hWnd;

		// create Direct3D device
		m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_d3ddev);
	
		if (!m_d3ddev)
		{
			OutputDebugString("[Error] CreateDevice failed\n");
			break;
		}

		// clear the back buffer to black
		m_d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		// create pointer to the back buffer
		m_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backbuffer);
		if (!m_backbuffer)
		{
			OutputDebugString("[ERROR] GetBackBuffer failed\n");
			break;
		}

		// Initialize sprite helper from Direct3DX helper library
		D3DXCreateSprite(m_d3ddev, &m_spriteHandler);
		if (!m_spriteHandler)
		{
			OutputDebugString("[ERROR] D3DXCreateSprite failed\n");
			break;
		}

		result = true;
	} while (false);

	return result;
}

void CDirect3D::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) const
{
	D3DXVECTOR3 position(x, y, 0);
	m_spriteHandler->Draw(texture, nullptr, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
}
