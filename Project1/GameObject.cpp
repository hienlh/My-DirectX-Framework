#include "GameObject.h"

bool CGameObject::Set_Texture(LPDIRECT3DDEVICE9 d3ddv, LPCSTR texturePath)
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
			d3ddv,       // Pointer to Direct3D device object
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
	}
	while (false);

	return result;
}

void CGameObject::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void CGameObject::Render(CDirect3D *pDirect3D) const
{
	pDirect3D->Draw(m_x, m_y, m_texture);
}
