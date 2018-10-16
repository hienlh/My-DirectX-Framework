#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "Scene.h"

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
	
	Framework::CScene* scene = Framework::CScene::Instantiate();
	pGameManager->SetCurrentScene(scene);

	do
	{		
		Framework::UObjectData data = { {} };
		Framework::CGameObject* mario = Framework::CGameObject::Instantiate(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

		data.renderData = { L"Resources\\mario.png" };
		mario->AddComponent({ Framework::EObjectType::RENDERER, data });

		mario->AddRigidbody(new CRigidbody(mario));
		mario->GetRigidbody()->SetVelocity(Vector2(1, 1));

		Framework::UObjectData data2 = { {} };
		data2.renderData = { L"Resources\\Block.png" };
		Framework::CGameObject* leftblock = Framework::CGameObject::Instantiate(Vector2(0, 0));
		leftblock->AddComponent({ Framework::EObjectType::RENDERER, data2 });

		leftblock->AddRigidbody(new CRigidbody(leftblock));
		leftblock->GetRigidbody()->SetVelocity(Vector2(0, 0));

		Framework::CGameObject* rightblock = Framework::CGameObject::Instantiate(Vector2(SCREEN_WIDTH - 10, 0));
		rightblock->AddComponent({ Framework::EObjectType::RENDERER, data2 });

		rightblock->AddRigidbody(new CRigidbody(rightblock));
		rightblock->GetRigidbody()->SetVelocity(Vector2(0, 0));
		
		//builderData.transformBuilder = { VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO };
		//mario->AddComponent(Framework::Object::EBuilderType::TRANSFORM, builderData);

		pGameManager->Run();
		
	} while (false);
	
	Framework::CGameManager::Destroy();
	Framework::CGraphic::Destroy();
	
	return 0;
}
