#include "Header.h"
#include "Direct3DCore.h"

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
	WPARAM returnValue = 0;
	do
	{
		//Framework::Direct3DCore::Direct3DCore::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, false);

		/*	CGameManager *pGame = CGameManager::GetInstance();
	
			bool result = pGame->Init(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT);
			if (!result)
			{
				OutputDebugString("[Error] CGameManager::Init failed\n");
				break;
			}
	
			pGame->Run();
		
			returnValue = pGame->Get_Message().wParam;
			pGame->Release();
	*/
	}
	while (false);

	return returnValue;
}
