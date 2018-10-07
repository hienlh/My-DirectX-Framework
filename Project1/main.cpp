#include "Macros.h"
#include "Header.h"
#include "GameManager.h"
#include "GameObject.h"
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
	Framework::GameManager::IGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	auto* pGameManager = Framework::GameManager::IGameManager::GetInstance();
	auto scene = CScene::Instantiate();
	pGameManager->SetCurrentScene(scene);

	do
	{
		Framework::Object::UBuilderData builderData = {{}};
		builderData.rendererBuilder = { "mario.png" };

		Framework::Object::CGameObject* mario = Framework::Object::CGameObject::Instantiate(Vector3(0, 0, 0));
		mario->AddComponent(Framework::Object::EBuilderType::RENDERER, builderData);

		Framework::Object::CGameObject* mario2 = Framework::Object::CGameObject::Instantiate(Vector3(0, 0, 0));
		mario2->AddComponent(Framework::Object::EBuilderType::RENDERER, builderData);

		Framework::Object::CGameObject* mario3 = Framework::Object::CGameObject::Instantiate(Vector3(0, 0, 0));
		mario3->AddComponent(Framework::Object::EBuilderType::RENDERER, builderData);

	

		/*builderData.transformBuilder = { VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO };
		mario->AddComponent(Framework::Object::EBuilderType::TRANSFORM, builderData);*/
		
		pGameManager->Run();

	} while (false);
	Framework::GameManager::IGameManager::Release();

	return 0;
}
