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
	// Game Manager
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	// Scene
	CScene* pScene = CScene::Instantiate();
	{
		pGameManager->SetCurrentScene(pScene);
		pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		pScene->GetMainCamera()->AddComponent<CameraController>();
	}

	// Resource Manager
	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	{
		pResourceManager->AddTexture(L"Background", L".\\Resources\\mini_background.png", NULL, ".\\Resources\\mini_background.xml");
		pResourceManager->AddTexture(L"Megaman", L".\\Resources\\Player\\MegaManXEdited.png", NULL, ".\\Resources\\Player\\MegaManXEdited.xml");
		pResourceManager->AddTexture(L"Megaman Dash", L".\\Resources\\Player\\MegaManX-Dash.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
		pResourceManager->AddTexture(L"Wall", L".\\Resources\\wall.png");
	}

	// Player Animations
	{
		struct AnimationInfo
		{
			CWString name = nullptr;
			CWString textureName = nullptr;
			DWORD startID, count;
			DWORD delayTime;
			bool loop;
		};

		AnimationInfo infoParams[] = {
			{ L"Megaman Init", L"Megaman", 0, 8, 100, false},
			{ L"Megaman Idle", L"Megaman", 8, 2, 100, true},
			{ L"Megaman Run", L"Megaman", 14, 10, 100, true},
			{ L"Megaman Jump Shoot", L"Megaman", 41, 3, 120, true},
			{ L"Megaman Dash", L"Megaman Dash", 0, 23, 20, false},
			{ L"Megaman Run Shoot", L"Megaman", 24, 10, 100, true},
			{ L"Megaman Jump",	L"Megaman", 39, 1, 100, false},
			{ L"Megaman Fall", L"Megaman", 37, 1, 120, false},
			{ L"Megaman Land Fall", L"Megaman", 38, 2, 120, false},
			{ L"Megaman Fall Shoot", L"Megaman", 44, 3, 120, true},
			{ L"Megaman Idle Shoot", L"Megaman", 10, 2, 120, false},
			{ L"Megaman Cling", L"Megaman", 49, 2, 100, false },
			{ L"Megaman Cling Fall", L"Megaman", 51, 1, 100, false },
			{ L"Megaman Cling Jump", L"Megaman", 52, 2, 100, false },
		};

		for (const AnimationInfo &info : infoParams)
			new CAnimation(info.name, info.textureName, info.startID, info.count, info.delayTime, info.loop);
	}

	{
		CGameObject* pBackground = new CGameObject(L"Background");
		pBackground->AddComponent<CRenderer>()->SetSprite(L"Background")->GetSprite()->SetAnchor(VECTOR2_ZERO);
		pBackground->GetComponent<CRenderer>()->SetZOrder(1);
		
		{
			const std::vector<CSprite*> &sprites = pResourceManager->GetTexture(L"Background")->m_sprites;

			for (size_t iSprite = 0; iSprite < sprites.size(); iSprite++)
			{
				CGameObject* pGround = new CGameObject((std::wstring(L"Ground") + std::to_wstring(iSprite)).c_str(),
					Vector2(sprites[iSprite]->GetSourceRect().left, sprites[iSprite]->GetSourceRect().top));
				pGround->AddComponent<CRigidbody>()->SetGravityScale(0);

				pGround->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
				pGround->GetComponent<CBoxCollider>()->SetIsDebugging(true);
				pGround->GetComponent<CBoxCollider>()->SetSize(sprites[iSprite]->GetSourceRect().Size());
				pGround->GetComponent<CBoxCollider>()->SetAnchor(VECTOR2_ZERO);
				pGround->GetComponent<CTransform>()->SetParent(pBackground);				
			}
		}

		CGameObject* pWall = new CGameObject(L"Wall Object", Vector2(200, 120));
		pWall->AddComponent<CRigidbody>()->SetGravityScale(0);
		pWall->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pWall->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pWall->GetComponent<CBoxCollider>()->SetAnchor(VECTOR2_ZERO);
		//pWall->AddComponent<CRenderer>()->SetSprite(L"Wall");
		//pWall->GetComponent<CTransform>()->SetParent(pBackground);

		CGameObject* pPlayer = new CGameObject(L"Player", Vector2(0, 0));
		pPlayer->GetComponent<CTransform>()->Set_Scale(Vector2(1, 1));
		pPlayer->AddComponent<CRenderer>()->SetFlipY(false);
		pPlayer->AddComponent<CAnimator>()->
			AddAnimation(L"Megaman Init")->
			AddAnimation(L"Megaman Idle")->
			AddAnimation(L"Megaman Idle Shoot")->
			AddAnimation(L"Megaman Jump")->
			AddAnimation(L"Megaman Fall")->
			AddAnimation(L"Megaman Land Fall")->
			AddAnimation(L"Megaman Run")->
			AddAnimation(L"Megaman Dash")->
			AddAnimation(L"Megaman Run Shoot")->
			AddAnimation(L"Megaman Cling")->
			AddAnimation(L"Megaman Cling Fall")->
			AddAnimation(L"Megaman Cling Jump")->

			AddBool(L"isIdle", false)->
			AddBool(L"isJump", false)->
			AddBool(L"isFall", false)->
			AddBool(L"isLandFall", false)->
			AddBool(L"isShoot", false)->
			AddBool(L"isRun", false)->
			AddBool(L"isDash", false)->
			AddBool(L"isClining", false)->

			AddTransition(L"Megaman Init", L"Megaman Idle")->
			AddTransition(L"Megaman Idle", L"Megaman Idle Shoot", true, L"isShoot", true)->
			AddTransition(L"Megaman Idle", L"Megaman Dash", true, L"isDash", true)->
			AddTransition(L"Megaman Idle", L"Megaman Jump", true, L"isJump", true)->
			AddTransition(L"Megaman Idle", L"Megaman Fall", true, L"isFall", true)->
			AddTransition(L"Megaman Idle", L"Megaman Run", true, L"isRun", true)->
			AddTransition(L"Megaman Dash", L"Megaman Idle")->
			AddTransition(L"Megaman Idle Shoot", L"Megaman Idle")->
			AddTransition(L"Megaman Jump", L"Megaman Fall", true, L"isFall", true)->
			AddTransition(L"Megaman Fall", L"Megaman Land Fall", true, L"isLandFall", true)->
			AddTransition(L"Megaman Land Fall", L"Megaman Idle")->
			AddTransition(L"Megaman Run", L"Megaman Idle", true, L"isRun", false)->
			AddTransition(L"Megaman Run", L"Megaman Jump", true, L"isJump", true)->
			AddTransition(L"Megaman Run", L"Megaman Run Shoot", true, L"isShoot", true, true)->
			AddTransition(L"Megaman Run Shoot", L"Megaman Run", true, L"isShoot", false, true)->
			AddTransition(L"Megaman Run", L"Megaman Dash", true, L"isDash", true)->
			AddTransition(L"Megaman Jump", L"Megaman Cling", true, L"isClining", true, false)->
			AddTransition(L"Megaman Cling", L"Megaman Cling Fall", true, L"isFall", true, false)->
			AddTransition(L"Megaman Cling", L"Megaman Cling Jump", true, L"isJump", true, false)->
			AddTransition(L"Megaman Cling Jump", L"Megaman Fall", true, L"isFall", true, false);

		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->GetComponent<CRigidbody>()->SetGravityScale(1);
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(30, 34));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
		pPlayer->AddComponent<PlayerController>();

		pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pPlayer;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		pGameManager->Run();
	}

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
