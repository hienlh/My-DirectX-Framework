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

	CResourceManager::GetInstance()->AddTexture(L"Car", L".\\Resources\\car.png");
	CResourceManager::GetInstance()->AddTexture(L"Ball", L".\\Resources\\ball.png");
	CResourceManager::GetInstance()->AddTexture(L"Block", L".\\Resources\\Block.png");
	CResourceManager::GetInstance()->AddTexture(L"Background", L".\\Resources\\Background.jpg");
	CResourceManager::GetInstance()->AddTexture(L"Mario", L".\\Resources\\mario.png");
	CResourceManager::GetInstance()->AddTexture(L"Megaman", L".\\Resources\\Megaman.png", D3DCOLOR_XRGB(50, 96, 166));

	new CSprite(L"Background", L"Background", nullptr);
	new CSprite(L"Block", L"Block");
	new CSprite(L"Megaman", L"Megaman", new Rect(25, 225, 64, 434));

	new CSprite(L"Mario Idle Right", L"Mario", new Rect(154, 246, 181, 260), Vector2(0, 0));
	new CSprite(L"Mario Walk Right 1", L"Mario", new Rect(154, 275, 181, 290));
	new CSprite(L"Mario Walk Right 2", L"Mario", new Rect(154, 304, 181, 321));
	new CSprite(L"Mario Sit Right", L"Mario", new Rect(239, 426, 257, 440), Vector2(0,0));

	new CSprite(L"Mario Idle Left", L"Mario", new Rect(154, 186, 181, 200), Vector2(0, 0));
	new CSprite(L"Mario Walk Left 1", L"Mario", new Rect(154, 155, 181, 171));
	new CSprite(L"Mario Walk Left 2", L"Mario", new Rect(154, 125, 181, 141));

	CAnimation* anim = new CAnimation(L"Mario Walk Right");
	anim->Add(L"Mario Idle Right");
	anim->Add(L"Mario Walk Right 1");
	anim->Add(L"Mario Walk Right 2");

	anim = new CAnimation(L"Mario Walk Left");
	anim->Add(L"Mario Idle Left");
	anim->Add(L"Mario Walk Left 1");
	anim->Add(L"Mario Walk Left 2");

	anim = new CAnimation(L"Mario Idle Right", 300);
	anim->Add(L"Mario Idle Right");
	//anim->Add(L"Mario Sit Right");
	anim = new CAnimation(L"Mario Idle Left");
	anim->Add(L"Mario Idle Left");

	do
	{
		CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
		pBackground->AddComponent<CRenderer>()->SetSprite(L"Background");
		pBackground->GetComponent<CRenderer>()->SetZOrder(1);

		CGameObject* pPlayer = CGameObject::Instantiate(L"Player", Vector2(20,20));
		pPlayer->GetComponent<CTransform>()->Set_Scale(Vector2(2,2));
		pPlayer->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Right");
		pPlayer->AddComponent<CAnimator>()->AddAnimation(L"Mario Idle Left");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Mario Idle Right");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Left");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Right");
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->GetComponent<CRigidbody>()->SetGravityScale(0);
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(16, 27));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);
		pPlayer->AddComponent<BallController>();

		CGameObject* pMario = CGameObject::Instantiate(L"Mario", Vector2(400, 200));
		pMario->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Right");
		pMario->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pMario->GetComponent<CRigidbody>()->SetGravityScale(0);
		pMario->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pMario->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pMario->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		CGameObject* pMario2 = CGameObject::Instantiate(L"Mario2", Vector2(500, 200));
		pMario2->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Right");
		pMario2->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pMario2->GetComponent<CRigidbody>()->SetGravityScale(0);
		pMario2->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pMario2->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pMario2->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		CGameObject* pMario3 = CGameObject::Instantiate(L"Mario3", Vector2(230, 200));
		pMario3->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Right");
		pMario3->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pMario3->GetComponent<CRigidbody>()->SetGravityScale(0);
		pMario3->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pMario3->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pMario3->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		CGameObject* pMario4 = CGameObject::Instantiate(L"Mario3", Vector2(160, 160));
		pMario4->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Left");
		pMario4->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pMario4->GetComponent<CRigidbody>()->SetGravityScale(0);
		pMario4->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pMario4->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pMario4->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		CGameObject* pLeftBlock = CGameObject::Instantiate(L"Ground", Vector2(0, 100));
		pLeftBlock->GetComponent<CTransform>()->Set_Scale(Vector2(1, -1));
		pLeftBlock->AddComponent<CRenderer>()->SetSprite(L"Megaman");
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
