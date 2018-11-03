#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "Animator.h"

#include <Windows.h>
#pragma comment(lib, "Framework.lib")

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
	Framework::CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	Framework::CGameManager* pGameManager = Framework::CGameManager::GetInstance();

	Framework::CScene* pScene = Framework::CScene::Instantiate();
	pGameManager->SetCurrentScene(pScene);

	Framework::CGameObject* pCat = Framework::CGameObject::Instantiate(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
	Framework::UObjectData data = { {} };
	data.animatorBuilder = { L".\\Resources\\meow.jpg", 4, 2, 6, 100 };
	pCat->AddComponent({ Framework::EObjectType::ANIMATOR, data });

	do
	{
		pGameManager->Run();
	} while (false);

	Framework::CGameManager::Destroy();
	
	return 0;
}
