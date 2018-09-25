#pragma once
#include "Header.h"
#include "Direct3D.h"
#include "GameObject.h"

class CGameManager
{
private:
	static CGameManager *m_instance;
	
	CDirect3D *m_pDirect3D;
	HWND m_hWnd;
	MSG m_message;
	bool m_fullscreen;

	CGameObject *m_pPlayer;

private:
	CGameManager()
	{
		m_pDirect3D = nullptr;
		m_hWnd = nullptr;
		m_message = {};
		m_fullscreen = false;
		m_pPlayer = nullptr;
	}
	~CGameManager()
	{
		m_pDirect3D->Release();
		SAFE_DELETE(m_pPlayer);
	}

public:
	static CGameManager* GetInstance()
	{
		SAFE_ALLOC(m_instance, CGameManager);
		return m_instance;
	}
	static void Release()
	{
		SAFE_DELETE(m_instance);
	}

private:
	bool InitWindow(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight);
	void LoadResources();

public:
	bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight);
	bool Render();
	void Run();

	MSG Get_Message() { return m_message; }
	HWND Get_WindowHandle()  { return m_hWnd; }
	CDirect3D* Get_Direct3D() { return m_pDirect3D; }

	bool CreatePlayer();
};