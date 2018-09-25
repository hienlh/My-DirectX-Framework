#pragma once
#include "Header.h"
#include "Direct3D.h"

class CGameObject 
{
protected:
	float m_x, m_y;
	LPDIRECT3DTEXTURE9 m_texture;

public:
	CGameObject()
	{
		m_x = m_y = 0;
		m_texture = nullptr;
	}
	~CGameObject()
	{
		m_texture->Release();
	}

public:
	bool Set_Texture(LPDIRECT3DDEVICE9 d3ddv, LPCSTR texturePath);
	void Set_Position(float x, float y);

	void Render(CDirect3D *pDirect3D);
};