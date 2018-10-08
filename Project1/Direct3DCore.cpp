#include "Direct3DCore.h"
#include "Macros.h"
#include "GameObject.h"
#include "GameManager.h"
#pragma comment(lib, "dxguid.lib")

using namespace Framework::Base;

// Internal Direct3D Core Class
class CDirect3DCore_Internal final : public IDirect3DCore
{
private:
	static CDirect3DCore_Internal* __instance;

	// Properties
private:
	LPDIRECT3D9 m_d3d = nullptr;
	LPDIRECT3DDEVICE9 m_d3ddev = nullptr;
	LPDIRECT3DSURFACE9 m_backbuffer = nullptr;
	LPD3DXSPRITE m_spriteHandler = nullptr;

	// Cons / Des
private:
	CDirect3DCore_Internal() = default;
	~CDirect3DCore_Internal() = default;

	// Getters / Setters
public:
	LPDIRECT3D9 Get_Direct3D() override { return this->m_d3d; }
	LPDIRECT3DDEVICE9 Get_Direct3DDevice() override { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 Get_BackBuffer() override { return this->m_backbuffer; }
	LPD3DXSPRITE Get_SpriteHandler() override { return m_spriteHandler; }

	// Override methods
public:
	bool Render(std::vector<Framework::Object::CGameObject*> list_game_objects) override
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

				for (auto list_game_object : list_game_objects)
				{
					list_game_object->Render();
				}

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
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) override
	{
		D3DXVECTOR3 position(x, y, 0);
		m_spriteHandler->Draw(texture, nullptr, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
	}
	LPDIRECT3DTEXTURE9 CreateTexture(LPCSTR texturePath) override;
	LPDIRECTINPUT8 CreateDirect() override;
	LPDIRECTINPUTDEVICE8 CreateKeyboard(LPDIRECTINPUT8 dinput) override;
	LPDIRECTINPUTDEVICE8 CreateMouse(LPDIRECTINPUT8 dinput) override;
	// Internal methods
private:
	bool Init(HWND hWind, bool fullscreen)
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
	void Destroy()
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

	// Static methods
public:
	static void Instantiate(HWND hWnd, bool fullscreen);
	static void Release();

	static CDirect3DCore_Internal* GetInstance();
};

// Direct Core Internal implementation

CDirect3DCore_Internal* CDirect3DCore_Internal::__instance = nullptr;

CDirect3DCore_Internal* CDirect3DCore_Internal::GetInstance()
{
	return __instance;
}

LPDIRECT3DTEXTURE9 CDirect3DCore_Internal::CreateTexture(LPCSTR texturePath)
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
		}

		hr = D3DXCreateTextureFromFileEx(
			m_d3ddev,       // Pointer to Direct3D device object
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

LPDIRECTINPUT8 CDirect3DCore_Internal::CreateDirect()
{
	LPDIRECTINPUT8 dinput = nullptr;
	HRESULT result = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<LPVOID*>(&dinput), nullptr);
	if (result != DI_OK)
		dinput = nullptr;

	return dinput;
}

LPDIRECTINPUTDEVICE8 CDirect3DCore_Internal::CreateKeyboard(LPDIRECTINPUT8 dinput)
{
	HWND hwnd = Framework::GameManager::IGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
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

LPDIRECTINPUTDEVICE8 CDirect3DCore_Internal::CreateMouse(LPDIRECTINPUT8 dinput)
{
	HWND hwnd = Framework::GameManager::IGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
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

void CDirect3DCore_Internal::Instantiate(HWND hWnd, bool fullscreen)
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CDirect3DCore_Internal);

		if (!__instance->Init(hWnd, fullscreen))
		{
			OutputDebugString("[Error] IDirect3DCore::Init failed\n");
			SAFE_DELETE(__instance);
		}
	}
}

void CDirect3DCore_Internal::Release()
{
	__instance->Destroy();
	SAFE_DELETE(__instance);
}

// Direct Core implementation

void IDirect3DCore::Instantiate(HWND hWnd, bool fullscreen)
{
	CDirect3DCore_Internal::Instantiate(hWnd, fullscreen);
}

void IDirect3DCore::Release()
{
	CDirect3DCore_Internal::Release();
}

IDirect3DCore * Framework::Base::IDirect3DCore::GetInstance()
{
	return CDirect3DCore_Internal::GetInstance();
}