#pragma once
#include "header.h"

// Direct3D class
class CDirect3D
{
private:
	static CDirect3D *m_instance;

	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_d3ddev;
	LPDIRECT3DSURFACE9 m_backbuffer;
	LPD3DXSPRITE m_spriteHandler;

private:
	CDirect3D()
	{
		m_d3d = nullptr;
		m_d3ddev = nullptr;
		m_backbuffer = nullptr;
		m_spriteHandler = nullptr;
	}
	~CDirect3D()
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

public:
	static CDirect3D* GetInstance()
	{
		SAFE_ALLOC(m_instance, CDirect3D);
		return m_instance;
	}
	static void Release()
	{
		SAFE_DELETE(m_instance);
	}

public:	
	bool Init(HWND hWnd, bool fullscreen);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) const;
	
	LPDIRECT3D9 Get_Direct3D() const { return this->m_d3d; }
	LPDIRECT3DDEVICE9 Get_Direct3DDevice() const { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 Get_BackBuffer() const { return this->m_backbuffer; }
	LPD3DXSPRITE Get_SpriteHandler() const { return m_spriteHandler; }
};