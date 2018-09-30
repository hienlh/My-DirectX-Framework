#include "Renderer.h"
#include "Macros.h"

using namespace Framework::Component;

bool CRenderer::Init(LPDIRECT3DDEVICE9 d3ddev, LPCSTR texturePath)
{
	bool result = false;
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
			d3ddev,       // Pointer to Direct3D device object
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

		result = true;
	} while (false);

	return result;
}

void CRenderer::Destroy()
{
	if (m_texture)
		m_texture->Release();	
}

CRenderer* CRenderer::Instantiate(LPDIRECT3DDEVICE9 d3ddev, LPCSTR texturePath)
{
	CRenderer* instance = nullptr;
	SAFE_ALLOC(instance, CRenderer);

	if (!instance->Init(d3ddev, texturePath))
		SAFE_DELETE(instance);

	return instance;
}

void CRenderer::Release(CRenderer* &instance)
{
	instance->Destroy();
	SAFE_DELETE(instance);
}
