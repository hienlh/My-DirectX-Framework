#pragma once
#include "header.h"
#include "CDirect3D.h"

class CGame
{
private:
	static CGame *m_instance;
	
	CDirect3D *m_pDirect3D;
	HWND m_hWnd;
	MSG m_message;
	
private:
	CGame() : m_pDirect3D(nullptr) {}
	
	~CGame() { m_pDirect3D->Release(); }

public:
	static CGame* GetInstance()
	{
		SAFE_ALLOC(m_instance, CGame);
		return m_instance;
	}

	static void Release()
	{
		SAFE_DELETE(m_instance);
	}

public:
	bool Init(HINSTANCE hInstance, int nShowCmd, int screenWidth, int screenHeight);

	bool Render();
	void Run();

	MSG Get_Message() { return m_message; }
	HWND Get_WindowHandle() { return m_hWnd; }
};

//struct SPRITE
//{
//	int x, y;
//	int width, height;
//	int movex, movey;
//	int curframe, lastframe;
//	int animdelay, animcount;
//};

//int GameInit(HWND hWnd);
//
//void GameRun(HWND hWnd);
