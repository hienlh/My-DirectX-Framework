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

private:
	CDirect3D() : m_d3d(nullptr), m_d3ddev(nullptr), m_backbuffer(nullptr) {}

	~CDirect3D()
	{
		if (m_d3d)
			m_d3d->Release();

		if (m_d3ddev)
			m_d3ddev->Release();

		if (m_backbuffer)
			m_backbuffer->Release();
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

	LPDIRECT3D9 Get_Direct3D() { return this->m_d3d; }
	LPDIRECT3DDEVICE9 Get_Direct3DDevice() { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 Get_BackBuffer() { return this->m_backbuffer; }
};