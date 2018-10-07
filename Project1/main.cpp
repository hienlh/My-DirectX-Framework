#include "Macros.h"
#include "Header.h"
#include "GameManager.h"
#include "GameObject.h"

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
	Framework::GameManager::IGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	auto* pGameManager = Framework::GameManager::IGameManager::GetInstance();
	do
	{
		auto* mario = Framework::Object::CGameObject::Instantiate();

		Framework::Object::UObjectData data = { {} };
		data.renderData = { MARIO_PATH };
		mario->AddComponent({Framework::Object::EObjectType::RENDERER, data});
	
		data.transformData = { VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO };
		mario->AddComponent({ Framework::Object::EObjectType::TRANSFORM, data });
		
		pGameManager->Run();

	} while (false);
	
	Framework::GameManager::IGameManager::Destroy();

	return 0;
}
