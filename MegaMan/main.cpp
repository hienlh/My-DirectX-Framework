#include "stdafx.h"
#include "Macros.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "CameraController.h"
#include "BallController.h"
#include "RightBlockController.h"
#include "LeftBlockController.h"
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
		/*CGameObject* pCat = CGameObject::Instantiate(L"Cat", Vector2(0,0));
		pCat->AddComponent<CAnimator>()->Set(L".\\Resources\\meow.jpg", 4, 2, 6, 100);
		pCat->AddComponent<CRigidbody>()->SetVelocity(Vector2(.1, 0));
		pCat->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pCat->GetComponent<CBoxCollider>()->SetSize(Vector2(pCat->GetComponent<CAnimator>()->GetAnimationWidth(), pCat->GetComponent<CAnimator>()->GetAnimationHeight()));
		pScene->AddGameObject(pCat);
		*/

		/*CGameObject *topCeiling = CGameObject::Instantiate(L"Top ceiling", Vector2(0, 0));
		topCeiling->AddComponent<CRigidbody>();
		topCeiling->AddComponent<CBoxCollider>()->SetSize(Vector2(SCREEN_WIDTH, 10));
		pScene->AddGameObject(topCeiling);

		CGameObject *bottomCeiling = CGameObject::Instantiate(L"Bottom ceiling", Vector2(0, SCREEN_HEIGHT));
		bottomCeiling->AddComponent<CRigidbody>();
		bottomCeiling->AddComponent<CBoxCollider>()->SetSize(Vector2(SCREEN_WIDTH, 10));
		pScene->AddGameObject(bottomCeiling);*/

		CGameObject *pBall = CGameObject::Instantiate(L"Ball", Vector2(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2));
		pBall->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\ball.png");
		pBall->AddComponent<CRigidbody>()->SetVelocity(Vector2(-.05, -.05));
		pBall->AddComponent<CBoxCollider>();
		pBall->AddComponent<BallController>();
		pScene->AddGameObject(pBall);
		
		CGameObject* leftBlock = CGameObject::Instantiate(L"Left Block", Vector2(50, 0));
		leftBlock->AddComponent<CRenderer>()->SetTexture(L"Resources\\Block.png");
		leftBlock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		leftBlock->AddComponent<CBoxCollider>();
		leftBlock->AddComponent<LeftBlockController>();

		CGameObject* rightBlock = CGameObject::Instantiate(L"Right Block", Vector2(SCREEN_WIDTH - 60, 0));
		rightBlock->AddComponent<CRenderer>()->SetTexture(L"Resources\\Block.png");
		rightBlock->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		rightBlock->AddComponent<CBoxCollider>();
		rightBlock->AddComponent<RightBlockController>();

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pBall;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();
	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	
	return 0;
}
