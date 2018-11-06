#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "CameraController.h"
#include "BallController.h"
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
	
	do
	{

		CGameObject* pCat = CGameObject::Instantiate(L"Cat", Vector2(0,0));
		pCat->AddComponent<CAnimator>()->Set(L".\\Resources\\meow.jpg", 4, 2, 6, 100);
		pCat->AddComponent<CRigidbody>()->SetVelocity(Vector2(.1, 0));
		pCat->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pCat->GetComponent<CBoxCollider>()->SetSize(Vector2(pCat->GetComponent<CAnimator>()->GetAnimationWidth(), pCat->GetComponent<CAnimator>()->GetAnimationHeight()));

		CGameObject*pBall = CGameObject::Instantiate(L"Ball", Vector2(SCREEN_WIDTH - 100, 0));
		pBall->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\ball.png");
		pBall->AddComponent<CRigidbody>();
		pBall->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pBall->AddComponent<BallController>();

		pScene->AddGameObject(pCat);
		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pBall;
		pScene->AddGameObject(pBall);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
