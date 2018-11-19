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
	CResourceManager::GetInstance()->AddTexture(L"Mario", L".\\Resources\\mario.png");

	CAnimation* anim = CAnimation::Instantiate(L"Mario Walk Right", L"Mario", 100);
	anim->Add(Rect(154, 246, 181, 260));
	anim->Add(Rect(154, 275, 181, 290));
	anim->Add(Rect(154, 304, 181, 321));
	anim->Add(Rect(154, 246, 181, 260));

	anim = CAnimation::Instantiate(L"Mario Walk Left", L"Mario", 100);
	anim->Add(Rect(154, 186, 181, 200));
	anim->Add(Rect(154, 155, 181, 171));
	anim->Add(Rect(154, 125, 181, 141));
	anim->Add(Rect(154, 186, 181, 200));

	anim = CAnimation::Instantiate(L"Mario Idle Right", L"Mario", 100);
	anim->Add(Rect(154, 246, 181, 260));
	anim = CAnimation::Instantiate(L"Mario Idle Left", L"Mario", 100);
	anim->Add(Rect(154, 186, 181, 200));

	do
	{
		/*CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
		pBackground->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\Background.jpg");*/

		CGameObject* pCat = CGameObject::Instantiate(L"Cat", Vector2(20,0));
		pCat->GetComponent<CTransform>()->Set_Rotation(Vector3(0, 0, 0));
		pCat->AddComponent<CAnimator>()->AddAnimation(L"Mario Idle Left");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Idle Right");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Left");
		pCat->GetComponent<CAnimator>()->AddAnimation(L"Mario Walk Right");
		pCat->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pCat->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pCat->GetComponent<CBoxCollider>()->SetSize(Vector2(16, 27));
		pCat->GetComponent<CBoxCollider>()->SetIsDebugging(false);
		pCat->AddComponent<BallController>();

		CGameObject* pLeftBlock = CGameObject::Instantiate(L"Ground", Vector2(0, SCREEN_HEIGHT/2));
		pLeftBlock->AddComponent<CRenderer>()->SetTexture(L"Block");
		pLeftBlock->AddComponent<CRigidbody>()->SetGravityScale(0);
		pLeftBlock->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pLeftBlock->GetComponent<CBoxCollider>()->SetIsDebugging(false);

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pCat;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
