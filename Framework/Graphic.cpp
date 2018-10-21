#include "Graphic.h"
#include "Macros.h"
#include "GameObject.h"
#include "GameManager.h"
#pragma comment(lib, "dxguid.lib")

using namespace Framework;

CGraphic* CGraphic::__instance = nullptr;

void CGraphic::Release()
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

// Direct Core implementation

bool CGraphic::Init(HWND hWind, bool fullscreen)
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
		GetClientRect(hWind, &rect); // retrieve Window width & height 

		d3dpp.BackBufferWidth = rect.right + 1;
		d3dpp.BackBufferHeight = rect.bottom + 1;
		d3dpp.hDeviceWindow = hWind;

		// create Direct3D device
		m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWind,
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

Vector2 CGraphic::GetImageSize(LPCSTR imagePath)
{
	D3DXIMAGE_INFO info;
	HRESULT hr = D3DXGetImageInfoFromFile(imagePath, &info);
	if (hr != S_OK)
	{
		OutputDebugString("[ERROR] D3DXGetImageInfoFromFile failed\n");
		return Vector2(-1, -1);
	}

	return Vector2(info.Width, info.Height);
}

void CGraphic::SetTransform(Matrix &orthographicMatrix, Matrix &identityMatrix, Matrix &viewMatrix)
{
	m_d3ddev->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	m_d3ddev->SetTransform(D3DTS_WORLD, &identityMatrix);
	m_d3ddev->SetTransform(D3DTS_VIEW, &viewMatrix);
}

bool CGraphic::Render(std::vector<CGameObject*> list_game_objects)
{
	bool result = false;
	do
	{
		// Start rendering
		m_pDevice->BeginScene();
		// Clear back buffer with black color
		m_pDevice->ColorFill(m_pBackBuffer, nullptr, COLOR_BLACK);

		m_pSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (CGameObject* pGameObject : gameObjectList)
			pGameObject->Render();

		m_pSpriteHandler->End();

		// stop rendering
		m_pDevice->EndScene();

		// display back buffer content to the screen
		m_d3ddev->Present(nullptr, nullptr, nullptr, nullptr);

		result = true;
	} while (false);

	return result;
}

void CGraphic::Draw(Texture* texture, Vector2 position, Rect* pSourceRect)
{
	Vector3 position3D = { position.x, position.y, 0 };
	m_pSpriteHandler->Draw(texture, pSourceRect, nullptr, &position3D, COLOR_WHITE);
}

Texture* CGraphic::CreateTexture(LPCWSTR texturePath, DWORD &textureWidth, DWORD &textureHeight)
{
	D3DXVECTOR3 position(x, y, 0);
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = height;
	rect.right = width;


	m_spriteHandler->Draw(texture, &rect, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
}

LPDIRECT3DTEXTURE9 CGraphic::CreateTexture(LPCSTR texturePath)
{
	LPDIRECT3DTEXTURE9 m_texture = nullptr;
	do
	{
		D3DXIMAGE_INFO info;
		HRESULT hr = D3DXGetImageInfoFromFile(texturePath, &info);
		if (hr != S_OK)
		{
			OutputDebugString("[ERROR] D3DXGetImageInfoFromFile failed\n");
			break;

		textureWidth = info.Width;
		textureHeight = info.Height;

		hr = D3DXCreateTextureFromFileExW(
			m_pDevice,       // Pointer to Direct3D device object
			texturePath, // Path to the image to load
			info.Width,  // Texture width
			info.Height, // Texture height
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 255, 255), // Transparent color
			&info,
			nullptr,
			&m_texture // Created texture pointer

		);


		if (hr != S_OK)
		{
			OutputDebugString("[ERROR] CreateTextureFromFile failed\n");
			break;
		}
	} while (false);

	return m_texture;
}

LPDIRECTINPUT8 CGraphic::CreateDirect()
{
	LPDIRECTINPUT8 dinput = nullptr;
	HRESULT result = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<LPVOID*>(&dinput), nullptr);

	if (result != DI_OK)
		dinput = nullptr;

	return dinput;
}

LPDIRECTINPUTDEVICE8 CGraphic::CreateKeyboard(LPDIRECTINPUT8 dinput)
{
	HWND hwnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	LPDIRECTINPUTDEVICE8 dikeyboard = nullptr;

	do
	{
		HRESULT result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
		if (result != DI_OK)
			break;

		result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (result != DI_OK)
			break;

		result = dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (result != DI_OK)
			break;

		result = dikeyboard->Acquire();
		if (result != DI_OK)
			break;

	} while (false);

	return dikeyboard;
}

LPDIRECTINPUTDEVICE8 CGraphic::CreateMouse(LPDIRECTINPUT8 dinput)
{
	HWND hwnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	LPDIRECTINPUTDEVICE8 dimouse = nullptr;
	do
	{
		HRESULT result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
		if (result != DI_OK)
			break;

		result = dimouse->SetDataFormat(&c_dfDIMouse);
		if (result != DI_OK)
			break;

		result = dimouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (result != DI_OK)
			break;

		result = dimouse->Acquire();
		if (result != DI_OK)
			break;

	} while (false);

	return dimouse;
}

void CGraphic::Instantiate(HWND hWnd, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CGraphic);

		if (!__instance->Init(hWnd, fullscreen))
		{
			OutputDebugString("[Error] CGraphic::Init failed\n");
			SAFE_DELETE(__instance);
		}
	}
}

void CGraphic::Destroy()
{
	__instance->Release();
	SAFE_DELETE(__instance);
}

CGraphic * CGraphic::GetInstance()
{
	return __instance;
}