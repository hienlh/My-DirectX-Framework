#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "CameraController.h"
#include "PlayerController.h"
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
	
	pResourceManager->AddTexture(L"Ground1", L".\\Resources\\ground1.jpg");
	pResourceManager->AddTexture(L"Ground2", L".\\Resources\\ground2.jpg");
	pResourceManager->AddTexture(L"Ground3", L".\\Resources\\ground3.jpg");
	pResourceManager->AddTexture(L"Ground4", L".\\Resources\\ground4.jpg");

	pResourceManager->AddTexture(L"Megaman Left", L".\\Resources\\megaman_left.png");
	pResourceManager->AddTexture(L"Megaman Right", L".\\Resources\\megaman_right.png");
	pResourceManager->AddTexture(L"Background", L".\\Resources\\mini_background.png");

	CAnimation* anim = CAnimation::Instantiate(L"Megaman Run Left", L"Megaman Left", 100);
	anim->Add({ Vector2(85, 66), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(121, 67), Vector2(34, 33) }, 0.05f);
	anim->Add({ Vector2(163, 66), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(200, 65), Vector2(25, 35) }, 0.05f);
	anim->Add({ Vector2(229, 66), Vector2(22, 34) }, 0.05f);
	anim->Add({ Vector2(257, 67), Vector2(26, 33) }, 0.05f);
	anim->Add({ Vector2(294, 67), Vector2(34, 33) }, 0.05f);
	anim->Add({ Vector2(336, 67), Vector2(32, 34) }, 0.05f);
	anim->Add({ Vector2(375, 66), Vector2(23, 35) }, 0.05f);
	anim->Add({ Vector2(403, 66), Vector2(20, 34) }, 0.05f);
	anim->Add({ Vector2(438, 66), Vector2(30, 34) }, 0.05f);

	anim = CAnimation::Instantiate(L"Megaman Run Right", L"Megaman Right", 100);
	anim->Add({ Vector2(5, 66), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(50, 66), Vector2(20, 34) }, 0.05f);
	anim->Add({ Vector2(75, 66), Vector2(23, 35) }, 0.05f);
	anim->Add({ Vector2(105, 67), Vector2(32, 34) }, 0.05f);
	anim->Add({ Vector2(145, 67), Vector2(22, 34) }, 0.05f);
	anim->Add({ Vector2(190, 67), Vector2(34, 33) }, 0.05f);
	anim->Add({ Vector2(222, 66), Vector2(26, 33) }, 0.05f);
	anim->Add({ Vector2(248, 66), Vector2(25, 35) }, 0.05f);
	anim->Add({ Vector2(248, 66), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(318, 67), Vector2(34, 33) }, 0.05f);
	anim->Add({ Vector2(359, 67), Vector2(30, 34) }, 0.05f);

	anim = CAnimation::Instantiate(L"Megaman Idle Left", L"Megaman Left", 100);
	anim->Add({ Vector2(113, 28), Vector2(30, 34) }, 0.05f);
	/*anim->Add({ Vector2(248, 66), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(182, 28), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(217, 28), Vector2(30, 34) }, 0.05f);*/
	
	anim = CAnimation::Instantiate(L"Megaman Idle Right", L"Megaman Right", 100);
	anim->Add({ Vector2(226, 28), Vector2(30, 34) }, 0.05f);
	/*anim->Add({ Vector2(261, 28), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(295, 28), Vector2(30, 34) }, 0.05f);
	anim->Add({ Vector2(330, 28), Vector2(30, 34) }, 0.05f);*/
	
	do
	{
		CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
		pBackground->AddComponent<CRenderer>()->SetTexture(L"Background");

		CGameObject* pPlayer = CGameObject::Instantiate(L"Player", Vector2(100, 0));
		pPlayer->GetComponent<CTransform>()->Set_Rotation(Vector3(0, 0, 0));
		pPlayer->AddComponent<CAnimator>()->AddAnimation(L"Megaman Idle Right");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Idle Left");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Run Left");
		pPlayer->GetComponent<CAnimator>()->AddAnimation(L"Megaman Run Right");
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(16, 27));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(false);
		pPlayer->AddComponent<PlayerController>();

		CGameObject* pGround1 = CGameObject::Instantiate(L"Ground1", Vector2(0, 178));
		pGround1->AddComponent<CRenderer>()->SetTexture(L"Ground1");
		pGround1->AddComponent<CRigidbody>()->SetGravityScale(0);
		pGround1->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		
		CGameObject* pGround2 = CGameObject::Instantiate(L"Ground2", Vector2(352, 132));
		pGround2->AddComponent<CRenderer>()->SetTexture(L"Ground2");
		pGround2->AddComponent<CRigidbody>()->SetGravityScale(0);
		pGround2->AddComponent<CBoxCollider>()->SetUsedByEffector(false);

		CGameObject* pGround3 = CGameObject::Instantiate(L"Ground3", Vector2(510, 82));
		pGround3->AddComponent<CRenderer>()->SetTexture(L"Ground3");
		pGround3->AddComponent<CRigidbody>()->SetGravityScale(0);
		pGround3->AddComponent<CBoxCollider>()->SetUsedByEffector(false);

		CGameObject* pGround4 = CGameObject::Instantiate(L"Ground4", Vector2(640, 178));
		pGround4->AddComponent<CRenderer>()->SetTexture(L"Ground4");
		pGround4->AddComponent<CRigidbody>()->SetGravityScale(0);
		pGround4->AddComponent<CBoxCollider>()->SetUsedByEffector(false);

		CGameObject* pCamera = pScene->GetMainCamera();
		pCamera->GetComponent<CameraController>()->m_target = pPlayer;
		pCamera->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
