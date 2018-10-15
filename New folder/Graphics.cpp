#include "Graphic.h"
#include "Macros.h"
#include "GameObject.h"

using namespace Framework::Base;

// Internal Direct3D Core Class
class CGraphic_Internal final : public IGraphic
{
private:
	static CGraphic_Internal* __instance;

	// Cons / Des
public:
	CGraphic_Internal() = default;
	virtual ~CGraphic_Internal() = default;

	// Properties
private:
	Direct3D* m_pDirect3D = nullptr;
	Device* m_pDevice = nullptr;
	Surface* m_pBackBuffer = nullptr;
	Sprite* m_pSpriteHandler = nullptr;

	// Getters / Setters
public:
	Direct3D* Get_Direct3D() override { return this->m_pDirect3D; }
	Device* Get_Device() override { return this->m_pDevice; }
	Surface* Get_BackBuffer() override { return this->m_pBackBuffer; }
	Sprite* Get_SpriteHandler() override { return m_pSpriteHandler; }

	// Override methods
public:
	bool Render(std::vector<Framework::Object::CGameObject*> list_game_objects) override
	{
		bool result = false;
		do
		{
			// Start rendering
			if (m_pDevice->BeginScene())
			{
				// Clear back buffer with black color
				m_pDevice->ColorFill(m_pBackBuffer, nullptr, D3DCOLOR_XRGB(0, 0, 0));

				m_pSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

				// Flag
				for (auto list_game_object : list_game_objects)
				{
					//list_game_object->Update();
				}

				m_pSpriteHandler->End();

				// stop rendering
				m_pDevice->EndScene();
			}

			// display back buffer content to the screen
			m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);

			result = true;
		} while (false);

		return result;
	}

	void Draw(Vector3 position, Texture* texture) override
	{
		m_pSpriteHandler->Draw(texture, nullptr, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
	}

	Texture* CreateTexture(CString texturePath) override
	{
		Texture* m_texture = nullptr;
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

	// Internal methods
private:
	bool Init(HWND hWind, bool fullscreen)
	{
		bool result = false;
		do
		{
			// initialize Direct3D
			m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
			if (!m_pDirect3D)
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
			m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWind,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pDevice);

			if (!m_pDevice)
			{
				OutputDebugString("[Error] CreateDevice failed\n");
				break;
			}

			// clear the back buffer to black
			m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

			// create pointer to the back buffer
			m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
			if (!m_pBackBuffer)
			{
				OutputDebugString("[ERROR] GetBackBuffer failed\n");
				break;
			}

			// Initialize sprite helper from Direct3DX helper library
			D3DXCreateSprite(m_pDevice, &m_pSpriteHandler);
			if (!m_pSpriteHandler)
			{
				OutputDebugString("[ERROR] D3DXCreateSprite failed\n");
				break;
			}

			result = true;
		} while (false);

		return result;
	}
	void Release()
	{
		if (m_pDirect3D)
			m_pDirect3D->Release();

		if (m_pDevice)
			m_pDevice->Release();

		if (m_pBackBuffer)
			m_pBackBuffer->Release();

		if (m_pSpriteHandler)
			m_pSpriteHandler->Release();
	}

	// Static methods
public:
	static void Instantiate(HWND hWnd, bool fullscreen);
	static void Destroy();

	static CGraphic_Internal* GetInstance();
};

// Direct Core Internal implementation

CGraphic_Internal* CGraphic_Internal::__instance = nullptr;

void CGraphic_Internal::Instantiate(HWND hWnd, bool fullscreen)
{
	SAFE_ALLOC(__instance, CGraphic_Internal);

	if (!__instance->Init(hWnd, fullscreen))
	{
		OutputDebugString("[Error] IDirect3DCore::Init failed\n");
		SAFE_DELETE(__instance);
	}
}

void CGraphic_Internal::Destroy()
{
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

CGraphic_Internal* CGraphic_Internal::GetInstance()
{
	return __instance;
}

// Direct Core implementation

void IGraphic::Instantiate(HWND hWnd, bool fullscreen)
{
	CGraphic_Internal::Instantiate(hWnd, fullscreen);
}

void IGraphic::Destroy()
{
	CGraphic_Internal::Destroy();
}

IGraphic* IGraphic::GetInstance()
{
	return CGraphic_Internal::GetInstance();
}