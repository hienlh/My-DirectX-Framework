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
#include "MegaManPowerController.h"
#include "BlastHornetController.h"
#pragma comment(lib, "Framework.lib")

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	CScene* pScene = new CScene("Main Scene", {8000,8000});
	pGameManager->SetCurrentScene(pScene);
	pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	pScene->GetMainCamera()->AddComponent<CameraController>();

	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	pResourceManager->AddTexture("Block", ".\\Resources\\Block.png");
	pResourceManager->AddTexture("Background", ".\\Resources\\Background.jpg");
	pResourceManager->AddTexture("MegaManX", ".\\Resources\\Player\\MegaManXEdited.png", NULL, ".\\Resources\\Player\\MegaManXEdited.xml");
	pResourceManager->AddTexture("MegaManX-Dash", ".\\Resources\\Player\\MegaManX-Dash.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture("MegaManX-Dash Shoot", ".\\Resources\\Player\\MegaManX-Dash Shoot.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture("MegaManX-Power", ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.png", NULL, ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.xml");
	// pResourceManager->AddTexture("MegaManX-Effect", ".\\Resources\\Player\\MegaManX-Effect.png", NULL, ".\\Resources\\Player\\MegaManX-Effect.xml");
	pResourceManager->AddTexture("Stairs", ".\\Resources\\Stairs.png");
	pResourceManager->AddTexture("MapObjects", ".\\Resources\\Map\\Objects.png", NULL, ".\\Resources\\Map\\Objects.xml");
	pResourceManager->AddTexture("Map", ".\\Resources\\Map\\Map.png", NULL, ".\\Resources\\Map\\Map.xml");
	pResourceManager->AddTexture("Blast_Hornet", ".\\Resources\\Blast Hornet\\sprites.png", NULL, ".\\Resources\\Blast Hornet\\sprites.xml");

	//From file MegaManXEdited.png
	new CAnimation("MegaManX Init", "MegaManX", 0, 2, 1000, false);
	new CAnimation("MegaManX InitLand", "MegaManX", 2, 6, 100, false);
	CAnimation* anim = new CAnimation("MegaManX Idle", "MegaManX", 8, 2, 100, true);
	anim->Add("MegaManX", 7, 1, 2000);
	anim = new CAnimation("MegaManX Idle Shoot", "MegaManX", 10, 3, 120, false);
	anim->Add("MegaManX", 11)
		->Add("MegaManX", 10);
	new CAnimation("MegaManX Run", "MegaManX", 14, 10, 100, true);
	new CAnimation("MegaManX Run Shoot", "MegaManX", 24, 10, 100, true);
	new CAnimation("MegaManX Fall", "MegaManX", 37, 1, 120, false);
	new CAnimation("MegaManX Fall Shoot", "MegaManX", 44, 1, 120, false);
	new CAnimation("MegaManX Landfall", "MegaManX", 38, 2, 120, false);
	new CAnimation("MegaManX Landfall Shoot", "MegaManX", 45, 2, 120, false);
	new CAnimation("MegaManX Jump", "MegaManX", 34, 3, 100, false);
	new CAnimation("MegaManX Jump Shoot", "MegaManX", 41, 3, 100, false);
	new CAnimation("MegaManX Wall Clinging", "MegaManX", 50, 2, 120, true);
	new CAnimation("MegaManX Wall Clinging Shoot", "MegaManX", 55, 2, 120, true);
	anim = new CAnimation("MegaManX ClimbLadder", "MegaManX", 62, 4, 100, true);
	anim->Add("MegaManX", 64)->Add("MegaManX", 63);

	//From file MegaManX-Dash Shoot.png
	new CAnimation("MegaManX Dash", "MegaManX-Dash", 0, 23, 20, false);
	new CAnimation("MegaManX Dash Shoot", "MegaManX-Dash Shoot", 0, 23, 20, false);

	//From file MegaManX-Effect.png
	// new CAnimation("MegaManX Smoke", "MegaManX-Effect", 0, 6, 20, false);

	//From file SNES_-_Mega_Man_X3_-_Zero.png
	new CAnimation("MegaManX Power", "MegaManX-Power", 0, 17, 30, true);

	//From file Map/Objects.png
	new CAnimation("MapBehind_1", "MapObjects", 29, 9, 100, true);

	pResourceManager->AddPrefab("MapBehind_1")
		->AddComponent<CAnimator>()->AddAnimation("MapBehind_1");

	do
	{
		CGameObject* pBackground = new CGameObject("Map");
		pBackground->AddComponent<CRenderer>()->SetSprite("Map")
			->SetZOrder(1)->GetSprite()->SetAnchor(VECTOR2_ZERO);
		{
			//Ground
			for (int i = 6; i < 6 + 9; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();
		
				CGameObject* pGround = new CGameObject("Ground" + std::to_string(i));
				pGround->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pGround->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pGround->AddComponent<CBoxCollider>()->SetIsDebugging(true);
				pGround->GetComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}
		
			//Ceiling
			for (int i = 0; i < 0 + 6; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();
		
				CGameObject* pCeiling = new CGameObject("Ceiling" + std::to_string(i));
				pCeiling->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pCeiling->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pCeiling->AddComponent<CBoxCollider>()->SetIsDebugging(true);
				pCeiling->GetComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}
		
			//Wall
			for (int i = 15; i < 15 + 8; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();
		
				CGameObject* pWall = new CGameObject("Wall" + std::to_string(i));
				pWall->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pWall->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pWall->AddComponent<CBoxCollider>()->SetIsDebugging(true);
				pWall->GetComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}
		}

		CGameObject* pPlayer = new CGameObject("Player", Vector2(45, 875));
		// CGameObject* pPlayer = new CGameObject("Player", Vector2(1810, 409));
		pPlayer->AddComponent<CAnimator>()
			->AddAnimation("MegaManX Init")
			->AddAnimation("MegaManX InitLand")
			->AddAnimation("MegaManX Idle")
			->AddAnimation("MegaManX Idle Shoot")
			->AddAnimation("MegaManX Jump")
			->AddAnimation("MegaManX Jump Shoot")
			->AddAnimation("MegaManX Fall")
			->AddAnimation("MegaManX Fall Shoot")
			->AddAnimation("MegaManX Landfall")
			->AddAnimation("MegaManX Landfall Shoot")
			->AddAnimation("MegaManX Run")
			->AddAnimation("MegaManX Dash")
			->AddAnimation("MegaManX Run Shoot")
			->AddAnimation("MegaManX Dash Shoot")
			->AddAnimation("MegaManX ClimbLadder")
			->AddAnimation("MegaManX Wall Clinging")
			->AddAnimation("MegaManX Wall Clinging Shoot")
			->AddAnimation("MegaManX Power")

			->AddBool("isIdle", false)
			->AddBool("isJump", false)
			->AddBool("isFall", false)
			->AddBool("isLandfall", false)
			->AddBool("isShoot", false)
			->AddBool("isRun", false)
			->AddBool("isDash", false)
			->AddBool("isClimbLadder", false)
			->AddBool("isClinging", false)

			->AddTransition("MegaManX Init", "MegaManX InitLand", true, "isLandfall", true)
			->AddTransition("MegaManX InitLand", "MegaManX Idle")

			->AddTransition("MegaManX Idle", "MegaManX Dash", true, "isDash", true)
			->AddTransition("MegaManX Idle", "MegaManX Jump", true, "isJump", true)
			->AddTransition("MegaManX Idle", "MegaManX Fall", true, "isFall", true)
			->AddTransition("MegaManX Idle", "MegaManX Run", true, "isRun", true)
			->AddTransition("MegaManX Idle", "MegaManX ClimbLadder", true, "isClimbLadder", true)
			->AddTransition("MegaManX Idle", "MegaManX Idle Shoot", true, "isShoot", true)
			->AddTransition("MegaManX Idle Shoot", "MegaManX Idle")
			->AddTransition("MegaManX Idle Shoot", "MegaManX Dash", true, "isDash", true)
			->AddTransition("MegaManX Idle Shoot", "MegaManX Jump", true, "isJump", true)
			->AddTransition("MegaManX Idle Shoot", "MegaManX Fall", true, "isFall", true)
			->AddTransition("MegaManX Idle Shoot", "MegaManX Run", true, "isRun", true)
			->AddTransition("MegaManX Idle Shoot", "MegaManX ClimbLadder", true, "isClimbLadder", true)

			->AddTransition("MegaManX Dash", "MegaManX Idle", false, "isDash", false)
			->AddTransition("MegaManX Dash", "MegaManX Dash Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Dash Shoot", "MegaManX Dash", true, "isShoot", false, true)


			->AddTransition("MegaManX Jump", "MegaManX Fall", true, "isFall", true)
			->AddTransition("MegaManX Jump", "MegaManX ClimbLadder", true, "isClimbLadder", true)
			->AddTransition("MegaManX Jump", "MegaManX Wall Clinging", true, "isClinging", true)
			->AddTransition("MegaManX Jump", "MegaManX Jump Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Jump Shoot", "MegaManX Jump", true, "isShoot", false, true)
			->AddTransition("MegaManX Jump Shoot", "MegaManX Fall", true, "isFall", true)
			->AddTransition("MegaManX Jump Shoot", "MegaManX ClimbLadder", true, "isClimbLadder", true)
			->AddTransition("MegaManX Jump Shoot", "MegaManX Wall Clinging", true, "isClinging", true)


			->AddTransition("MegaManX Fall", "MegaManX Landfall", true, "isLandfall", true)
			->AddTransition("MegaManX Fall", "MegaManX Fall Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Fall Shoot", "MegaManX Fall", true, "isShoot", false, true)
			->AddTransition("MegaManX Fall Shoot", "MegaManX Landfall", true, "isLandfall", true)

			->AddTransition("MegaManX Landfall", "MegaManX Idle")
			->AddTransition("MegaManX Landfall", "MegaManX Landfall Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Landfall Shoot", "MegaManX Landfall", true, "isShoot", false, true)
			->AddTransition("MegaManX Landfall Shoot", "MegaManX Idle")

			->AddTransition("MegaManX Run", "MegaManX Idle", true, "isRun", false)
			->AddTransition("MegaManX Run", "MegaManX Jump", true, "isJump", true)
			->AddTransition("MegaManX Run", "MegaManX Dash", true, "isDash", true)
			->AddTransition("MegaManX Run", "MegaManX Run Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Run Shoot", "MegaManX Run", true, "isShoot", false, true)
			->AddTransition("MegaManX Run Shoot", "MegaManX Idle", true, "isRun", false)
			->AddTransition("MegaManX Run Shoot", "MegaManX Jump", true, "isJump", true)
			->AddTransition("MegaManX Run Shoot", "MegaManX Dash", true, "isDash", true)

			->AddTransition("MegaManX ClimbLadder", "MegaManX Idle", true, "isClimbLadder", false)

			->AddTransition("MegaManX Wall Clinging", "MegaManX Idle", true, "isClinging", false)
			->AddTransition("MegaManX Wall Clinging", "MegaManX Jump", true, "isJump", true)
			->AddTransition("MegaManX Wall Clinging", "MegaManX Wall Clinging Shoot", true, "isShoot", true, true)
			->AddTransition("MegaManX Wall Clinging Shoot", "MegaManX Wall Clinging", true, "isShoot", true, true)
		;
		pPlayer->GetComponent<CTransform>()->Set_Scale(Vector2(1, 1));
		pPlayer->GetComponent<CRenderer>()->SetFlipY(false);
		pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
		pPlayer->GetComponent<CRigidbody>()->SetGravityScale(1);
		pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(30, 34));
		pPlayer->GetComponent<CBoxCollider>()->SetIsDebugging(false);
		pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
		pPlayer->AddComponent<PlayerController>()->SetSpeed(0.1);
		

		Vector2 PlayerPos = pPlayer->GetComponent<CTransform>()->Get_Position();
		CGameObject* pPowerEffect = new CGameObject("Power Effect", Vector2(PlayerPos.x, PlayerPos.y));
		pPowerEffect->AddComponent<CAnimator>()
			->AddBool("isPowering", false)
			->AddAnimation("MegaManX Power");
		pPowerEffect->GetComponent<CTransform>()->SetParent(pPlayer);
		pPowerEffect->AddComponent<CRenderer>()->SetZOrder(-1);
		pPowerEffect->AddComponent<MegaManPowerController>();
		//CGameObject::Instantiate(pPlayer, pPlayer, Vector2(50, 50));

		//CGameObject::Instantiate("MapBehind_1", nullptr, {500, 500})->GetComponent<CRenderer>()->SetZOrder(-1);





		//Blast Hornet
		{
			//Add animation
			new CAnimation("BlastHornet_Flying", "Blast_Hornet", 3, 1);
			CAnimation* temp = new CAnimation("BlastHornet_StartAttacking", "Blast_Hornet", 3, 13, 100, false);
			temp->Add("Blast_Hornet", 9, -1, 200);
			new CAnimation("BlastHornet_Shooting", "Blast_Hornet", 16, 5, 100, false);
			new CAnimation("BlastHornet_Died", "Blast_Hornet", 21, 1);
			//Setting properties
			CGameObject* pHornet = new CGameObject("Blast Hornet", Vector2(1840, 461));
			pHornet->AddComponent<CAnimator>()
				->AddAnimation("BlastHornet_Flying")
				->AddAnimation("BlastHornet_StartAttacking")
				->AddAnimation("BlastHornet_Shooting")
				->AddAnimation("BlastHornet_Died")
				->AddBool("isAttack", false)
				->AddBool("isShoot", false)
				->AddBool("isDead", false)

				->AddTransition("BlastHornet_Flying","BlastHornet_StartAttacking",true,"isAttack",true)
				->AddTransition("BlastHornet_StartAttacking", "BlastHornet_Flying", false, "isAttack", false)
				->AddTransition("BlastHornet_Flying", "BlastHornet_Shooting", true, "isShoot", true)
				->AddTransition("BlastHornet_Shooting", "BlastHornet_Flying", false, "isShoot", false)
				->AddTransition("BlastHornet_Shooting", "BlastHornet_Flying", false, "isShoot", false)
				->AddTransition("BlastHornet_Flying", "BlastHornet_Died", true, "isDead", true)
				->AddTransition("BlastHornet_StartAttacking", "BlastHornet_Died", false, "isDead", true)
				->AddTransition("BlastHornet_Shooting", "BlastHornet_Died", false, "isDead", true)
			;
			pHornet->AddComponent<CRenderer>()->SetSprite("Blast_Hornet",3);
			pHornet->AddComponent<CRigidbody>()->SetGravityScale(0);
			pHornet->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pHornet->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
			pHornet->GetComponent<CBoxCollider>()->SetIsDebugging(true);
			pHornet->AddComponent<BlastHornetController>();
			pHornet->GetComponent<BlastHornetController>()->m_target = pPlayer;
	
			//Initatiate Blast Hornet Wing
			new CAnimation("BlastHornet_Wing", "Blast_Hornet", 0, 3, 50,true);
			Vector2 HornetPos = pHornet->GetComponent<CTransform>()->Get_Position();
			CGameObject* pHornetWing = new CGameObject("Blast Hornet Wing", Vector2(HornetPos.x, HornetPos.y-30));
			pHornetWing->AddComponent<CTransform>()->SetParent(pHornet);
			pHornetWing->AddComponent<CRenderer>();
			pHornetWing->AddComponent<CAnimator>()
				->AddAnimation("BlastHornet_Wing");


			//Camera
			pScene->GetMainCamera()->GetComponent<CameraController>()->m_target = pPlayer;
			pScene->GetMainCamera()->GetComponent<CameraController>()->SetIsFollow(true);
		}

		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
