<<<<<<< HEAD
#include "../Framework/Macros.h"
#include "../Framework/Header.h"
#include "../Framework/GameManager.h"
#include "../Framework/GameObject.h"
#include "../Framework/Graphic.h"
#include "../Framework/Input.h"
#include "../Framework/Rigidbody.h"
#include "../Framework/BoxCollider.h"
#include "../Framework/Camera.h"
#include "BallController.h"
#include "BlockController.h"
#include "CameraController.h"
=======
#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "Animator.h"
>>>>>>> origin/dev

#include <Windows.h>
#pragma comment(lib, "Framework.lib")

LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
<<<<<<< HEAD
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	auto* pGameManager = CGameManager::GetInstance();
	auto scene = CScene::Instantiate();
	pGameManager->SetCurrentScene(scene);
	scene->GetMainCamera()->AddComponent<CameraController>();
	scene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	do
	{
		CGameObject* Background = CGameObject::Instantiate(String("Background"), Vector2(0, 0));
		CGameObject* ball = CGameObject::Instantiate(String("Mario"), Vector2(SCREEN_WIDTH / 2, 0));
		//CGameObject* mario2 = CGameObject::Instantiate(String("Mario2"), Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 27));
		CGameObject* leftBlock = CGameObject::Instantiate(String("Left Block"), Vector2(50, 0));
		CGameObject* rightBlock = CGameObject::Instantiate(String("Right Block"), Vector2(SCREEN_WIDTH - 60, 0));

		Background->AddComponent<CRenderer>()->SetTexture(String("Background.jpg"));

		ball->AddComponent<CRenderer>()->SetTexture(String("Resources\\ball.png"));
		ball->AddComponent<CRigidbody>()->SetVelocity(Vector2(0.5, 0.5));
		ball->AddComponent<CBoxCollider>();
		ball->AddComponent<BallController>()->leftBlock = leftBlock;
		ball->GetComponent<BallController>()->rightBlock = rightBlock;

		/*mario2->AddComponent<CRenderer>()->SetTexture(String("mario.png"));
		mario2->AddComponent<CRigidbody>()->SetVelocity(Vector2(1, -1));
		mario2->AddComponent<CBoxCollider>();
		mario2->AddComponent<BallController>()->leftBlock = leftblock;
		mario2->GetComponent<BallController>()->rightBlock = rightblock;*/

		leftBlock->AddComponent<CRenderer>()->SetTexture(String("Resources\\Block.png"));
		leftBlock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		leftBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		leftBlock->AddComponent<BlockController>()->SetAllParameters(true, false);

		rightBlock->AddComponent<CRenderer>()->SetTexture(String("Block.png"));
		rightBlock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		rightBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		rightBlock->AddComponent<BlockController>()->SetAllParameters(true, true);

		//scene->GetMainCamera()->GetComponent<CameraController>()->m_target = mario;
		scene->AddGameObjects(3, ball, leftBlock, rightBlock);

=======
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
>>>>>>> origin/dev
		pGameManager->Run();
	} while (false);

	Framework::CGameManager::Destroy();
	
	return 0;
}
