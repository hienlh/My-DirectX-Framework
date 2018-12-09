#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "CameraController.h"
#include "BallController.h"
#include "ResourceManager.h"
#pragma comment(lib, "Framework.lib")

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	CScene* pScene = CScene::Instantiate();
	pGameManager->SetCurrentScene(pScene);
	pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	pScene->GetMainCamera()->AddComponent<CameraController>();

	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	pResourceManager->AddTexture(L"Block", L".\\Resources\\Block.png");
	pResourceManager->AddTexture(L"Background", L".\\Resources\\Background.jpg");
	pResourceManager->AddTexture(L"MegaManX", L".\\Resources\\Player\\MegaManXEdited.png", NULL, ".\\Resources\\Player\\MegaManXEdited.xml");
	pResourceManager->AddTexture(L"MegaManX-Dash", L".\\Resources\\Player\\MegaManX-Dash.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");


	new CAnimation(L"MegaManX Init", L"MegaManX", 0, 8, 100, false);

	CAnimation *anim = new CAnimation(L"MegaManX Idle", L"MegaManX", 8, 2, 100, true);
	anim->Add(L"MegaManX", 7, 0, 2000);

	new CAnimation(L"MegaManX Run", L"MegaManX", 14, 10, 100, true);

	new CAnimation(L"MegaManX Dash", L"MegaManX-Dash", 0, 23, 20, false);

	new CAnimation(L"MegaManX Run Shoot", L"MegaManX", 24, 10, 100, true);

	anim = new CAnimation(L"MegaManX Jump", L"MegaManX", 39, 1, 100, false);
	anim->Add(L"MegaManX", 38)
		->Add(L"MegaManX", 37)
		->Add(L"MegaManX", 36);
	
	new CAnimation(L"MegaManX Jump Shoot", L"MegaManX", 41, 3, 120, true);

	new CAnimation(L"MegaManX Fall", L"MegaManX", 37, 1, 120, false);
	new CAnimation(L"MegaManX Landfall", L"MegaManX", 38, 2, 120, false);

	new CAnimation(L"MegaManX Fall Shoot", L"MegaManX", 44, 3, 120, true);

	anim = new CAnimation(L"MegaManX Idle Shoot", L"MegaManX", 10, 2, 120, false);
	anim->Add(L"MegaManX", 11)->Add(L"MegaManX", 10);


	do
	{
		CGameObject* pBackground = new CGameObject(L"Background");
		pBackground->AddComponent<CRenderer>()->SetSprite(L"Background");
		pBackground->GetComponent<CRenderer>()->SetZOrder(1);

		CGameObject* pPlayer = new CGameObject(L"Player", Vector2(50, 50));
		pPlayer->GetComponent<CTransform>()->Set_Scale(Vector2(1, 1));
		pPlayer->AddComponent<CRenderer>()->SetFlipY(false);
		pPlayer->AddComponent<CAnimator>()->AddAnimation(L"MegaManX Init")->
			AddAnimation(L"MegaManX Idle")->
			AddAnimation(L"MegaManX Idle Shoot")->
			AddAnimation(L"MegaManX Jump")->
			AddAnimation(L"MegaManX Fall")->
			AddAnimation(L"MegaManX Landfall")->
			AddAnimation(L"MegaManX Run")->
			AddAnimation(L"MegaManX Dash")->
			AddAnimation(L"MegaManX Run Shoot")->
			AddBool(L"isIdle", false)->
			AddBool(L"isJump", false)->
			AddBool(L"isFall", false)->
			AddBool(L"isLandfall", false)->
			AddBool(L"isShoot", false)->
			AddBool(L"isRun", false)->
			AddBool(L"isDash", false)->
			AddTransition(L"MegaManX Init", L"MegaManX Idle")->
			AddTransition(L"MegaManX Idle", L"MegaManX Idle Shoot", true, L"isShoot", true)->
			AddTransition(L"MegaManX Idle", L"MegaManX Dash", true, L"isDash", true)->
			AddTransition(L"MegaManX Idle", L"MegaManX Jump", true, L"isJump", true)->
			AddTransition(L"MegaManX Idle", L"MegaManX Fall", true, L"isFall", true)->
			AddTransition(L"MegaManX Idle", L"MegaManX Run", true, L"isRun", true)->
			AddTransition(L"MegaManX Dash", L"MegaManX Idle")->
			AddTransition(L"MegaManX Idle Shoot", L"MegaManX Idle")->
			AddTransition(L"MegaManX Jump", L"MegaManX Fall", true, L"isFall", true)->
			AddTransition(L"MegaManX Fall", L"MegaManX Landfall", true, L"isLandfall", true)->
			AddTransition(L"MegaManX Landfall", L"MegaManX Idle")->
			AddTransition(L"MegaManX Run", L"MegaManX Idle", true, L"isRun", false)->
			AddTransition(L"MegaManX Run", L"MegaManX Jump", true, L"isJump", true)->
			AddTransition(L"MegaManX Run", L"MegaManX Run Shoot", true, L"isShoot", true, true)->
			AddTransition(L"MegaManX Run Shoot", L"MegaManX Run", true, L"isShoot", false, true)->
			AddTransition(L"MegaManX Run", L"MegaManX Dash", true, L"isDash", true);
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->GetComponent<CRigidbody>()->SetGravityScale(1);
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(30, 34));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
		pPlayer->AddComponent<BallController>();

		CGameObject* pTest = new CGameObject(L"test", Vector2(100, 100));
		pTest->GetComponent<CTransform>()->SetParent(pPlayer);
		pTest->AddComponent<CRenderer>()->SetSprite(L"MegaManX", 8);
		pTest->AddComponent<CAnimator>()->AddAnimation(L"MegaManX Run Shoot");


		CGameObject* pLeftBlock = new CGameObject(L"Ground", Vector2(100, 300));
		pLeftBlock->AddComponent<CRenderer>()->SetSprite(L"Block");
		pLeftBlock->GetComponent<CRenderer>()->SetZOrder(0);
		pLeftBlock->AddComponent<CRigidbody>()->SetGravityScale(0);
		pLeftBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pLeftBlock->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pLeftBlock->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pPlayer;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(false);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
