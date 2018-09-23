#include "header.h"

#include "GameManager.h"

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
	CGameManager *pGame = nullptr;
	do 
	{
		pGame = CGameManager::GetInstance();
		
		bool result = pGame->Init(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (!result)
		{
			OutputDebugString("[Error] CGame::Init failed\n");
			break;
		}
		pGame->LoadResources();

		pGame->Run();

	} while (false);

	WPARAM returnValue = pGame->Get_Message().wParam;
	pGame->Release();

	return returnValue;
}