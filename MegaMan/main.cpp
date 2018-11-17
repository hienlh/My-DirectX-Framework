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
		/*CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
		pBackground->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\Background.jpg");*/

		CGameObject* pCat = CGameObject::Instantiate(L"Cat", Vector2(0,0));
		pCat->GetComponent<CTransform>()->Set_Rotation(Vector3(0, 0, 0));
		pCat->AddComponent<CAnimator>()->Set(L".\\Resources\\car.png", 3, 1, 3, 100);
		pCat->AddComponent<CRigidbody>()->SetVelocity(Vector2(.1, 0));
		pCat->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pCat->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pCat->GetComponent<CBoxCollider>()->SetSize(Vector2(pCat->GetComponent<CAnimator>()->GetAnimationWidth(), pCat->GetComponent<CAnimator>()->GetAnimationHeight()));

		CGameObject*pBall = CGameObject::Instantiate(L"Ball", Vector2(SCREEN_WIDTH - 50, 50));
		pBall->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\ball.png");
		pBall->AddComponent<CRigidbody>();
		pBall->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pBall->AddComponent<BallController>();
		pBall->GetComponent<CBoxCollider>()->SetIsDebugging(true);

		CGameObject* pLeftBlock = CGameObject::Instantiate(L"Left Block", VECTOR2_ZERO);
		pLeftBlock->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\Block.png");
		pLeftBlock->AddComponent<CRigidbody>();
		pLeftBlock->AddComponent<CBoxCollider>();
		pLeftBlock->GetComponent<CBoxCollider>()->SetIsDebugging(true);

		CGameObject* pRightBlock = CGameObject::Instantiate(L"Left Block", Vector2(SCREEN_WIDTH - 10,0));
		pRightBlock->AddComponent<CRenderer>()->SetTexture(L".\\Resources\\Block.png");
		pRightBlock->AddComponent<CRigidbody>();
		pRightBlock->AddComponent<CBoxCollider>();
		pRightBlock->GetComponent<CBoxCollider>()->SetIsDebugging(true);

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pCat;
		//pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
