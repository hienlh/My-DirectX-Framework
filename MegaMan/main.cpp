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

	new CSprite(L"Mario Idle Right", L"Mario", new Rect(154, 246, 181, 260), Vector2(1, 1));
	new CSprite(L"Mario Walk Right 1", L"Mario", new Rect(154, 275, 181, 290));
	new CSprite(L"Mario Walk Right 2", L"Mario", new Rect(154, 304, 181, 321));
	new CSprite(L"Mario Sit Right", L"Mario", new Rect(239, 426, 257, 440), Vector2(1,1));

	new CSprite(L"Mario Idle Left", L"Mario", new Rect(154, 186, 181, 200), Vector2(1, 1));
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
	anim->Add(L"Mario Sit Right");
	anim = new CAnimation(L"Mario Idle Left");
	anim->Add(L"Mario Idle Left");

	do
	{
		CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(30, 0));
		pBackground->AddComponent<CRenderer>()->SetSprite(L"Background");
		pBackground->GetComponent<CRenderer>()->SetZOrder(1);

		CGameObject* pCat = CGameObject::Instantiate(L"Cat", Vector2(20,20));
		pCat->GetComponent<CTransform>()->Set_Scale(Vector2(2,2));
		pCat->AddComponent<CRenderer>()->SetSprite(L"Mario Idle Right");
		pCat->AddComponent<CAnimator>()->AddAnimation(L"Mario Idle Left");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Idle Right");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Left");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Right");
		pCat->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		//pCat->GetComponent<CRigidbody>()->SetGravityScale(0);
		pCat->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pCat->GetComponent<CBoxCollider>()->SetSize(Vector2(16, 27));
		pCat->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pCat->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);
		pCat->AddComponent<BallController>();

		CGameObject* pLeftBlock = CGameObject::Instantiate(L"Ground", Vector2(0, 100));
		pLeftBlock->GetComponent<CTransform>()->Set_Scale(Vector2(1, -1));
		pLeftBlock->AddComponent<CRenderer>()->SetSprite(L"Megaman");
		pLeftBlock->GetComponent<CRenderer>()->SetZOrder(0);
		pLeftBlock->AddComponent<CRigidbody>()->SetGravityScale(0);
		pLeftBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pLeftBlock->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pLeftBlock->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pCat;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
