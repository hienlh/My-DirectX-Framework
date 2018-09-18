#include "header.h"

#include "CGame.h"
#include "CDirect3D.h"

LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}

	return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	bool result = true;
	CGame *pGame = nullptr;

	do 
	{
		pGame = CGame::GetInstance();
		
		result = pGame->Init(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (!result)
		{
			MessageBox(pGame->Get_WindowHandle(), "[Error] CGame::Init failed", "Error", MB_OK);
			break;
		}

		pGame->Run();

	} while (false);

	WPARAM returnValue = pGame->Get_Message().wParam;
	pGame->Release();

	return returnValue;
}