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
	pResourceManager->AddTexture(L"Car", L".\\Resources\\car.png");
	pResourceManager->AddTexture(L"Ball", L".\\Resources\\ball.png");
	pResourceManager->AddTexture(L"Block", L".\\Resources\\Block.png");
	pResourceManager->AddTexture(L"Background", L".\\Resources\\Background.jpg");
	pResourceManager->AddTexture(L"Mario", L".\\Resources\\mario.png");
	pResourceManager->AddTexture(L"Megaman", L".\\Resources\\Megaman.png", D3DCOLOR_XRGB(50, 96, 166));
	pResourceManager->AddTexture(L"Megaman Left", L".\\Resources\\megaman_left.png", D3DCOLOR_XRGB(0, 0, 0), ".\\Resources\\megaman_left.xml");
	pResourceManager->AddTexture(L"Megaman Right", L".\\Resources\\megaman_right.png", D3DCOLOR_XRGB(0, 0, 0), ".\\Resources\\megaman_right.xml");

	CAnimation*anim = new CAnimation(L"Megaman Walk Right", L"Megaman Right", 18, 11);

	do
	{
		CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
		pBackground->AddComponent<CRenderer>()->SetSprite(L"Background");
		pBackground->GetComponent<CRenderer>()->SetZOrder(1);

		CGameObject* pPlayer = CGameObject::Instantiate(L"Player", Vector2(20,20));
		pPlayer->GetComponent<CTransform>()->Set_Scale(Vector2(2,2));
		pPlayer->AddComponent<CRenderer>()->SetSprite(L"Mario")->SetFlipX(true);
		pPlayer->AddComponent<CAnimator>()->AddAnimation(L"Megaman Walk Right");
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->GetComponent<CRigidbody>()->SetGravityScale(0);
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(16, 27));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);
		pPlayer->AddComponent<BallController>();

		CGameObject* pLeftBlock = CGameObject::Instantiate(L"Ground", Vector2(0, 100));
		pLeftBlock->GetComponent<CTransform>()->Set_Scale(Vector2(1, -1));
		pLeftBlock->AddComponent<CRenderer>()->SetSprite(L"Block");
		pLeftBlock->GetComponent<CRenderer>()->SetZOrder(0);
		pLeftBlock->AddComponent<CRigidbody>()->SetGravityScale(0);
		pLeftBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pLeftBlock->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pLeftBlock->GetComponent<CBoxCollider>()->SetAutoBoundSize(true);

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pPlayer;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
