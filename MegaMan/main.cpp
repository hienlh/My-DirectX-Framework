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
#include "MachineController.h"
#include "NotorBangerEnemyController.h"
#include "BusterShotController.h"
#include "HeadGunnerEnemyController.h"
#include "GenjiBosController.h"
#include "ShurikeinController.h"
#include "../Framework/Renderer.h"
#pragma comment(lib, "Framework.lib")

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	CScene* pScene = new CScene("Main Scene", { 8000,8000 });
	pGameManager->SetCurrentScene(pScene);
	pGameManager->SetIsDebugging(true);
	pScene->GetMainCamera()->GetComponent<CTransform>()->Set_Position(Vector2(128, 896));//128, 896));
	pScene->GetMainCamera()->AddComponent<CameraController>();
	pScene->SetIsRenderQuadTree(true);


#define Texture_EnemiesAndBosses "Texture_EnemiesAndBosses"
	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	pResourceManager->AddTexture("MegaManX", ".\\Resources\\Player\\MegaManXEdited.png", NULL, ".\\Resources\\Player\\MegaManXEdited.xml");
	pResourceManager->AddTexture("MegaManX-Dash", ".\\Resources\\Player\\MegaManX-Dash.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture("MegaManX-Dash Shoot", ".\\Resources\\Player\\MegaManX-Dash Shoot.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture("MegaManX-Power", ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.png", NULL, ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.xml");
	// pResourceManager->AddTexture("MegaManX-Effect", ".\\Resources\\Player\\MegaManX-Effect.png", NULL, ".\\Resources\\Player\\MegaManX-Effect.xml");
	pResourceManager->AddTexture("Stairs", ".\\Resources\\Stairs.png");
	pResourceManager->AddTexture("MapObjects", ".\\Resources\\Map\\Objects.png", NULL, ".\\Resources\\Map\\Objects.xml");
	pResourceManager->AddTexture("Map", ".\\Resources\\Map\\Map.png", NULL, ".\\Resources\\Map\\Map.xml");
	pResourceManager->AddTexture("WeaponsAndItems", ".\\Resources\\Weapons and Items\\Weapons and Items.png", NULL, ".\\Resources\\Weapons and Items\\Weapons and Items.xml");
	pResourceManager->AddTexture(Texture_EnemiesAndBosses, ".\\Resources\\Enemies\\enemies_and_bosses.png", NULL, ".\\Resources\\Enemies\\enemies_and_bosses.xml");

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
	new CAnimation("Machine_1_Run", "MapObjects", 25, 3, 50, true);
	new CAnimation("Machine_1_Idle", "MapObjects", 25, 1, 50, true);

	// Notor Banger
	{
		new CAnimation("Notor Banger Idle", "Texture_EnemiesAndBosses", 98, 1, 100, true);
		new CAnimation("Notor Banger Jump", "Texture_EnemiesAndBosses", 99, 3, 100, false);

		new CAnimation("Notor Banger 0", "Texture_EnemiesAndBosses", 106, 1);
		new CAnimation("Notor Banger 30", "Texture_EnemiesAndBosses", 107, 1);
		new CAnimation("Notor Banger 45", "Texture_EnemiesAndBosses", 108, 1);
		new CAnimation("Notor Banger 60", "Texture_EnemiesAndBosses", 109, 1);
		new CAnimation("Notor Banger 90", "Texture_EnemiesAndBosses", 110, 1);
	}

	auto pMapBehindPrefab = pResourceManager->AddPrefab("MapBehind_1");
	pMapBehindPrefab->AddComponent<CAnimator>()->AddAnimation("MapBehind_1");

	// Notor Banger
	{
		// Animations
		{
#define Animation_NotorBangerIdle "Animation_NotorBangerIdle"
#define Animation_NotorBangerJump "Animation_NotorBangerJump"

#define Animation_NotorBanger0 "Animation_NotorBanger0"
#define Animation_NotorBanger30 "Animation_NotorBanger30"
#define Animation_NotorBanger45 "Animation_NotorBanger45"
#define Animation_NotorBanger60 "Animation_NotorBanger60"
#define Animation_NotorBanger90 "Animation_NotorBanger90"

			new CAnimation(Animation_NotorBangerIdle, Texture_EnemiesAndBosses, 98, 1, 100, false);
			new CAnimation(Animation_NotorBangerJump, Texture_EnemiesAndBosses, 99, 3, 100, false);

			new CAnimation(Animation_NotorBanger0, Texture_EnemiesAndBosses, 106, 1, 100, false);
			new CAnimation(Animation_NotorBanger30, Texture_EnemiesAndBosses, 107, 1, 100, false);
			new CAnimation(Animation_NotorBanger45, Texture_EnemiesAndBosses, 108, 1, 100, false);
			new CAnimation(Animation_NotorBanger60, Texture_EnemiesAndBosses, 109, 1, 100, false);
			new CAnimation(Animation_NotorBanger90, Texture_EnemiesAndBosses, 110, 1, 100, false);
		}

		// Prefab
		{
#define Prefab_NotorBanger "Prefab_NotorBanger"

			std::string animationNames[] = { Animation_NotorBangerIdle, Animation_NotorBangerJump, Animation_NotorBanger0, Animation_NotorBanger30,
				Animation_NotorBanger45, Animation_NotorBanger60, Animation_NotorBanger90 };

#define BoolIdle "isIdle"
#define BoolJump "isJump"
#define Bool0 "is0"
#define Bool30 "is30"
#define Bool45 "is45"
#define Bool60 "is60"
#define Bool90 "is90"

			std::string boolNames[] = { BoolIdle, BoolJump, Bool0, Bool30, Bool45, Bool60, Bool90 };

			auto pPrefab = pResourceManager->AddPrefab(Prefab_NotorBanger);
			pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 98);
			pPrefab->AddComponent<CAnimator>()
				->AddAnimation(Animation_NotorBangerIdle)
				->AddAnimation(Animation_NotorBangerJump)
				->AddAnimation(Animation_NotorBanger0)
				->AddAnimation(Animation_NotorBanger30)
				->AddAnimation(Animation_NotorBanger45)
				->AddAnimation(Animation_NotorBanger60)
				->AddAnimation(Animation_NotorBanger90)

				->AddBool(BoolIdle, true)
				->AddBool(BoolJump, false)
				->AddBool(Bool0, false)
				->AddBool(Bool30, false)
				->AddBool(Bool45, false)
				->AddBool(Bool60, false)
				->AddBool(Bool90, false)

				->AddTransition(Animation_NotorBangerIdle, Animation_NotorBangerJump, false, BoolJump, true)
				->AddTransition(Animation_NotorBangerJump, Animation_NotorBangerIdle, true, BoolIdle, true);

			CAnimator* animator = pPrefab->GetComponent<CAnimator>();
			for (size_t iAnimationSource = 0; iAnimationSource < _countof(animationNames); iAnimationSource++)
			{
				for (size_t iAnimationDestination = iAnimationSource + 1; iAnimationDestination < _countof(animationNames); iAnimationDestination++)
				{
					animator->AddTransition(animationNames[iAnimationSource], animationNames[iAnimationDestination],
						false, boolNames[iAnimationDestination], true);

					animator->AddTransition(animationNames[iAnimationDestination], animationNames[iAnimationSource],
						false, boolNames[iAnimationSource], true);
				}
			}

			pPrefab->GetComponent<CTransform>()->Set_Scale(Vector2(1, 1));
			pPrefab->GetComponent<CRenderer>()->SetFlipY(false);
			pPrefab->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
			pPrefab->GetComponent<CRigidbody>()->SetGravityScale(1);
			pPrefab->GetComponent<CRigidbody>()->SetLimitedArea({ {120,880}, {200,50} });
			pPrefab->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pPrefab->GetComponent<CBoxCollider>()->SetOffset({ 0,5 });
			pPrefab->AddComponent<NotorBangerEnemyController>()->SetSpeed(0.1)
				;
		}
	}

	// Head Gunner
	{
		// Animations
		{
#define Animation_HeadGunnerIdle "Animation_HeadGunnerIdle"
#define Animation_HeadGunnerShoot1 "Animation_HeadGunnerShoot1"
#define Animation_HeadGunnerShoot2 "Animation_HeadGunnerShoot2"
#define Animation_HeadGunnerEnd "Animation_HeadGunnerEnd"


			new CAnimation(Animation_HeadGunnerIdle, Texture_EnemiesAndBosses, 45, 1, 200, false);
			new CAnimation(Animation_HeadGunnerShoot1, Texture_EnemiesAndBosses, 46, 3, 200, false);
			new CAnimation(Animation_HeadGunnerShoot2, Texture_EnemiesAndBosses, 49, 3, 200, false);
			new CAnimation(Animation_HeadGunnerEnd, Texture_EnemiesAndBosses, 52, 1, 200, false);
		}

		// Prefab
		{
#define Prefab_HeadGunner "Prefab_HeadGunner"

			auto pPrefab = pResourceManager->AddPrefab(Prefab_HeadGunner);
			pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 45);
			pPrefab->AddComponent<CAnimator>()
				->AddAnimation(Animation_HeadGunnerIdle)
				->AddAnimation(Animation_HeadGunnerShoot1)
				->AddAnimation(Animation_HeadGunnerShoot2)
				->AddAnimation(Animation_HeadGunnerEnd)

#define BoolShoot "isShoot"

				->AddBool(BoolShoot, false)

				->AddTransition(Animation_HeadGunnerIdle, Animation_HeadGunnerShoot1, true, BoolShoot, true)
				->AddTransition(Animation_HeadGunnerShoot1, Animation_HeadGunnerShoot2, true, BoolShoot, true)
				->AddTransition(Animation_HeadGunnerShoot2, Animation_HeadGunnerEnd, true)
				->AddTransition(Animation_HeadGunnerEnd, Animation_HeadGunnerIdle, true)
				;

			pPrefab->GetComponent<CTransform>()->Set_Scale(Vector2(1, 1));
			pPrefab->GetComponent<CRenderer>()->SetFlipY(false);
			pPrefab->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
			pPrefab->GetComponent<CRigidbody>()->SetGravityScale(1);
			pPrefab->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pPrefab->AddComponent<HeadGunnerEnemyController>()->SetSpeed(0.1)
				;
		}
	}

	do
	{
		CGameObject* pBackground = new CGameObject("Map");
		pBackground->AddComponent<CRenderer>()->SetSprite("Map")
			->SetZOrder(10)->GetSprite()->SetAnchor(VECTOR2_ZERO);
		{
			//Ground
			for (int i = 13; i < 13 + 25; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();

				CGameObject* pGround = new CGameObject("Ground" + std::to_string(i - 13));
				pGround->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pGround->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pGround->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}

			//Ceiling
			for (int i = 0; i < 0 + 13; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();

				CGameObject* pCeiling = new CGameObject("Ceiling" + std::to_string(i));
				pCeiling->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pCeiling->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pCeiling->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}

			//Wall
			for (int i = 38; i < 38 + 19; i++)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite("Map", i)->GetSourceRect();

				CGameObject* pWall = new CGameObject("Wall" + std::to_string(i - 38));
				pWall->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pWall->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pWall->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}
		}

		CGameObject* pMachine1 = new CGameObject("Machine_1");
		pMachine1->GetComponent<CTransform>()->Set_Position(Vector2(895, 960));
		pMachine1->AddComponent<CRenderer>()->SetSprite("MapObjects", 25)->SetZOrder(-1);
		pMachine1->AddComponent<CAnimator>()
			->AddAnimation("Machine_1_Idle")
			->AddAnimation("Machine_1_Run")
			->AddBool("isRun", false)
			->AddTransition("Machine_1_Idle", "Machine_1_Run", true, "isRun", true)
			->AddTransition("Machine_1_Run", "Machine_1_Idle", true, "isRun", false);
		pMachine1->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
		pMachine1->GetComponent<CBoxCollider>()->PlusSize(Vector2(-6, -20));
		pMachine1->GetComponent<CRigidbody>()->SetGravityScale(0)->SetLimitedArea(Rect(Vector2(895, 400), Vector2(0, 560)));
		pMachine1->AddComponent<MachineController>();

		//Player
		//CGameObject* pPlayer = new CGameObject("Player", Vector2(45, 875));
		CGameObject* pPlayer = new CGameObject("Player", Vector2(2255, 1170));
		{
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
				->AddTransition("MegaManX Fall", "MegaManX Wall Clinging", true, "isClinging", true)
				->AddTransition("MegaManX Fall Shoot", "MegaManX Fall", true, "isShoot", false, true)
				->AddTransition("MegaManX Fall Shoot", "MegaManX Landfall", true, "isLandfall", true)
				->AddTransition("MegaManX Fall Shoot", "MegaManX Wall Clinging", true, "isClinging", true)

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
				//->AddTransition("MegaManX Wall Clinging", "MegaManX Jump", true, "isJump", true)
				->AddTransition("MegaManX Wall Clinging", "MegaManX Wall Clinging Shoot", true, "isShoot", true, true)
				->AddTransition("MegaManX Wall Clinging Shoot", "MegaManX Wall Clinging", true, "isShoot", true, true)
				;
			pPlayer->GetComponent<CRenderer>()->SetFlipY(false);
			pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
			pPlayer->GetComponent<CRigidbody>()->SetGravityScale(1);
			pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(30, 34));
			pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
			pPlayer->AddComponent<PlayerController>()->SetSpeed(0.1);

			CGameObject* pPowerEffect = new CGameObject("Power Effect", Vector2(800, 875));
			pPowerEffect->SetIsActive(false);
			pPowerEffect->GetComponent<CTransform>()->SetParent(pPlayer);
			pPowerEffect->AddComponent<CRenderer>()->SetZOrder(-1);
			pPowerEffect->AddComponent<CAnimator>()
				->AddAnimation("MegaManX Power");
			pPlayer->GetComponent<PlayerController>()->m_Power = pPowerEffect;
		}

		CGameObject* pNotorBangerEnemy = CGameObject::Instantiate(Prefab_NotorBanger, nullptr, Vector2(200, 875));
		pNotorBangerEnemy->GetComponent<NotorBangerEnemyController>()->SetTarget(pPlayer);

		CGameObject* pHeadGunnerEnemy = CGameObject::Instantiate(Prefab_HeadGunner, nullptr, Vector2(450, 875));
		pHeadGunnerEnemy->GetComponent<HeadGunnerEnemyController>()->SetTarget(pPlayer);

		//Weapons and Items
		{
			//Buster Shots
			{
				new CAnimation("Animation_BusterShot_Init", "WeaponsAndItems", 0, 1, 100, false);
				new CAnimation("Animation_BusterShot_Explosive", "WeaponsAndItems", 1, 3, 100, false);
				auto pBusterBullet = pResourceManager->AddPrefab("BusterShot");
				pBusterBullet->AddComponent<CAnimator>()
					->AddAnimation("Animation_BusterShot_Init")
					->AddAnimation("Animation_BusterShot_Explosive")
					->AddBool("isCollision", false)
					->AddTransition("Animation_BusterShot_Init", "Animation_BusterShot_Explosive", true, "isCollision", true);
				pBusterBullet->GetComponent<CRenderer>()->SetZOrder(-10);
				pBusterBullet->AddComponent<CRigidbody>()->SetGravityScale(0);
				pBusterBullet->AddComponent<CBoxCollider>()->SetSize({ 1,1 })->SetIsTrigger(true);
				pBusterBullet->AddComponent<BusterShotController>();
			}
		}

		//Genji Bos
		{
			//Add Animation
			new CAnimation("GenjiBos", Texture_EnemiesAndBosses, 33, 4, 100, true);
			CGameObject* pGenjiBos = new CGameObject("Genji Bos", { 2477,980 });
			pGenjiBos->AddComponent<CRenderer>();
			pGenjiBos->AddComponent<CAnimator>()
				->AddAnimation("GenjiBos");
			pGenjiBos->AddComponent<CRigidbody>()->SetGravityScale(0);
			pGenjiBos->SetIsActive(false);
			pGenjiBos->AddComponent<GenjiBosController>()->m_target = pPlayer;
			pPlayer->GetComponent<PlayerController>()->m_GenjiBos = pGenjiBos;


			//Left Missle
			new CAnimation("GenjiBosMissle_down", Texture_EnemiesAndBosses, 38, 2, 50);
			Vector2 GenjiPpos = pGenjiBos->GetComponent<CTransform>()->Get_Position();
			CGameObject* pGenjiLeftMissle = new CGameObject("Genji Bos Missle", Vector2(GenjiPpos.x - 10, GenjiPpos.y + 6));
			pGenjiLeftMissle->AddComponent<CTransform>()->SetParent(pGenjiBos);
			pGenjiLeftMissle->AddComponent<CRenderer>()->SetFlipX(true);
			pGenjiLeftMissle->AddComponent<CAnimator>()
				->AddAnimation("GenjiBosMissle_down");

			//Bottom led
			/*new CAnimation("GenjiBos_light", "EnermiesBosses", 44, 1);*/
			CGameObject *pGenjiLight = new CGameObject("Genji Bos Light", Vector2(GenjiPpos.x, GenjiPpos.y + 40));
			pGenjiLight->AddComponent<CTransform>()->SetParent(pGenjiBos);
			pGenjiLight->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 44);
			pGenjiLight->SetIsActive(false);
			pGenjiBos->AddComponent<GenjiBosController>()->m_light = pGenjiLight;

			//Shurikein
			new CAnimation("Shurikein_Init", Texture_EnemiesAndBosses, 116, 72, 10, false);
			new CAnimation("Shurikein_Spinning", Texture_EnemiesAndBosses, 180, 7, 2, true);
			anim= new CAnimation("Shurikein_WasHit", Texture_EnemiesAndBosses, 180, 1, 50, true);
			anim->Add(Texture_EnemiesAndBosses, 182)
				->Add(Texture_EnemiesAndBosses, 184)
				->Add(Texture_EnemiesAndBosses, 186)
				->Add(Texture_EnemiesAndBosses, 205);
				
			anim= new CAnimation("Shurikein_WasHit_3D", Texture_EnemiesAndBosses, 187, 17, 2, true);
			for (int i = 203; i > 186; --i)
			{
				anim->Add(Texture_EnemiesAndBosses, i);
			}
			anim->Add(Texture_EnemiesAndBosses, 205)
				->Add(Texture_EnemiesAndBosses, 205)
				->Add(Texture_EnemiesAndBosses, 205);

			CGameObject *pShurikein = new CGameObject("Shurikein", Vector2(2477, 1181));
			pGenjiBos->GetComponent<GenjiBosController>()->m_shurikein = pShurikein;
			pShurikein->AddComponent<CAnimator>()
				->AddAnimation("Shurikein_Init")
				->AddAnimation("Shurikein_WasHit")
				->AddAnimation("Shurikein_WasHit_3D")
				->AddAnimation("Shurikein_Spinning")

				->AddBool("isWasHit", false)
				->AddTransition("Shurikein_Init", "Shurikein_Spinning")
				->AddTransition("Shurikein_WasHit", "Shurikein_Spinning")
				->AddTransition("Shurikein_Spinning", "Shurikein_WasHit", true, "isWasHit", true)
				;
			pShurikein->AddComponent<ShurikeinController>();
			pShurikein->AddComponent<CRigidbody>()->SetLimitedArea({ {2320, 1040}, {225, 161} })->SetGravityScale(0);
			pShurikein->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			pShurikein->GetComponent<CBoxCollider>()->SetSize(Vector2(47, 47));
			pShurikein->SetIsActive(false);



		}

		auto pMapBehind = CGameObject::Instantiate("MapBehind_1", pScene->GetMainCamera(), { 0, 0 });
		pMapBehind->GetComponent<CRenderer>()->SetZOrder(-1);
		pMapBehind->AddComponent<CRenderer>()->SetZOrder(20);

		pMachine1->GetComponent<MachineController>()->m_player = pPlayer;
		pScene->GetMainCamera()->GetComponent<CameraController>()->m_player = pPlayer;
		pScene->GetMainCamera()->GetComponent<CameraController>()->SetState(CameraState::Following);

		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();

	return 0;
}