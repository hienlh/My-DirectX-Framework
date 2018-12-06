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
using namespace std;

void ParseXML(const char* fileName, vector<Rect> &info, size_t depth)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	tinyxml2::XMLElement* parent = doc.FirstChildElement();
	for (size_t iDepth = 0; iDepth < depth - 1; iDepth++)
		parent = parent->FirstChildElement();

	// Count sprites stored in xml for resize
	size_t spriteCount = 0;
	for (tinyxml2::XMLNode* node = parent->FirstChild(); node; node = node->NextSibling())
		spriteCount++;

	info.resize(spriteCount);

	// Load attributes
	tinyxml2::XMLElement* child = parent->FirstChildElement();
	for (size_t iSprite = 0; iSprite < info.size(); iSprite++)
	{
		info[iSprite] = { Vector2(child->IntAttribute("x"), child->IntAttribute("y")),
									Vector2(child->IntAttribute("w"), child->IntAttribute("h")) };
		child = child->NextSiblingElement();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Game Manager
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	// Scene
	CScene* pScene = CScene::Instantiate();
	pGameManager->SetCurrentScene(pScene);
	{
		pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		pScene->GetMainCamera()->AddComponent<CameraController>();
	}

	// Resource Manager
	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	{
		//pResourceManager->AddTexture(L"Megaman Left", L".\\Resources\\megaman_left.png");
		pResourceManager->AddTexture(L"Megaman", L".\\Resources\\_megaman.png");
		pResourceManager->AddTexture(L"Background", L".\\Resources\\mini_background.png");
		pResourceManager->AddTexture(L"Intro Enemies", L".\\Resources\\Intro Enemies.png");
	}

	// Player
	vector<Rect> megaman;
	ParseXML(".\\Resources\\_megaman.xml", megaman, 2);
	{
		struct AnimationInfo
		{
			CWString name = nullptr;
			CWString textureName = nullptr;
			DWORD delayTime;
			DWORD startID, count;
			bool loop;
		};
		
		AnimationInfo infoParams[] = { 
			// Line 1
			{ L"Megaman Init",			L"Megaman", 0.1f, 0, 6, false},
			{ L"Megaman Idle",			L"Megaman", 0.1f, 7, 1, false},
			{ L"Megaman Idle Hit",		L"Megaman", 0.1f, 8, 3, true},
			{ L"Megaman Idle Shoot",	L"Megaman", 0.1f, 11, 2, true},
			// Line 2
			{ L"Megaman Run",			L"Megaman", 0.1f, 13, 11, true},
			// Line 3
			{ L"Megaman Run Shoot",		L"Megaman", 0.1f, 24, 10, true},
			// Line 4
			{ L"Megaman Jump",			L"Megaman", 0.1f, 34, 3, false},
			{ L"Megaman Fall",			L"Megaman", 0.1f, 37, 4, false},
			{ L"Megaman Jump Shoot",	L"Megaman", 0.1f, 41, 3, false},
			{ L"Megaman Fall Shoot",	L"Megaman", 0.1f, 44, 4, false},
		};
		CAnimation* animation = nullptr;
		for (const AnimationInfo &info : infoParams)
		{
			animation = CAnimation::Instantiate(info.name, info.textureName, info.loop);
			for (size_t iAnimation = info.startID; iAnimation < info.startID + info.count; iAnimation++)
				animation->Add(megaman[iAnimation], info.delayTime);
		}
	}

	// Grounds
	vector<Rect> grounds;
	{
		ParseXML(".\\Resources\\mini_background.xml", grounds, 2);

		for (size_t iGround = 0; iGround < grounds.size(); iGround++)
		{
			CGameObject* pGround = CGameObject::Instantiate((wstring(L"Ground") + to_wstring(iGround)).c_str(),
				Vector2(grounds[iGround].left, grounds[iGround].top));
			pGround->AddComponent<CRigidbody>()->SetGravityScale(0);
			pGround->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pGround->GetComponent<CBoxCollider>()->SetIsDebugging(true);
			pGround->GetComponent<CBoxCollider>()->SetSize(Vector2(grounds[iGround].right - grounds[iGround].left,
				grounds[iGround].bottom - grounds[iGround].top));
		}
	}

	CGameObject* pBackground = CGameObject::Instantiate(L"Background", Vector2(0, 0));
	pBackground->AddComponent<CRenderer>()->SetTexture(L"Background");

	// Player components
	CGameObject* pPlayer = CGameObject::Instantiate(L"Player", Vector2(100, 0));
	{
		pPlayer->GetComponent<CTransform>()->Set_Rotation(Vector3(0, 0, 0));
		pPlayer->AddComponent<CRenderer>();
		CAnimator* playerAnimator = pPlayer->AddComponent<CAnimator>();
		
		playerAnimator->AddState(L"Megaman Init");
		playerAnimator->AddState(L"Megaman Idle");
		playerAnimator->AddState(L"Megaman Idle Hit");
		playerAnimator->AddState(L"Megaman Idle Shoot");
		playerAnimator->AddState(L"Megaman Run");
		playerAnimator->AddState(L"Megaman Run Shoot");
		playerAnimator->AddState(L"Megaman Jump");
		playerAnimator->AddState(L"Megaman Fall");
		playerAnimator->AddState(L"Megaman Idle Shoot");

		playerAnimator->AddTransition(L"Megaman Idle", L"Megaman Run")->SetCondition(L"Run", true);// PlayerController::EStateCode::S_RUN);
		playerAnimator->AddTransition(L"Megaman Run", L"Megaman Idle")->SetCondition(L"Idle", true);// PlayerController::EStateCode::S_IDLE);
		playerAnimator->AddTransition(L"Megaman Idle", L"Megaman Jump")->SetCondition(L"Jump", true);// ::EStateCode::S_JUMP);
		playerAnimator->AddTransition(L"Megaman Jump", L"Megaman Idle")->SetCondition(L"Idle", true);// PlayerController::EStateCode::S_IDLE);
		playerAnimator->AddTransition(L"Megaman Idle", L"Megaman Idle Shoot")->SetCondition(L"Idle Shoot", true);// , PlayerController::EStateCode::S_IDLE_SHOOT);
		playerAnimator->AddTransition(L"Megaman Idle Shoot", L"Megaman Idle")->SetCondition(L"Idle", true);// , PlayerController::EStateCode::S_IDLE);
		
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(25, 35));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(true);
		pPlayer->AddComponent<PlayerController>();
	}

	// Camera
	CGameObject* pCamera = pScene->GetMainCamera();
	{
		pCamera->GetComponent<CameraController>()->m_target = pPlayer;
		pCamera->GetComponent<CameraController>()->SetIsFollow(true);
	}

	pGameManager->Run();

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();

	return 0;
}
