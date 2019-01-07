#include "stdafx.h"
#include "../Framework/Macros.h"
#include "../Framework/GameManager.h"
#include "../Framework/GameObject.h"
#include "../Framework/Rigidbody.h"
#include "../Framework/BoxCollider.h"
#include "../Framework/Animator.h"
#include "../Framework/Camera.h"
#include "../Framework/ResourceManager.h"
#include "../Framework/Graphic.h"

#include "CameraController.h"
#include "PlayerController.h"
#include "MachineController.h"
#include "NotorBangerEnemyController.h"
#include "BusterShotController.h"
#include "HeadGunnerEnemyController.h"
#include "GenjiBosController.h"
#include "Macros.h"
#include "BulletController.h"
#include "CanAttacked.h"
#include "CanBeAttacked.h"
#include "HealthValueController.h"
#include "Renderer.h"
#include "DoorController.h"
#include "EffectAutoRemove.h"
#include "DashFullEffect.h"
#include "EffectPool.h"
#include "BulletPool.h"
#include "BuildingController.h"
#include "CarryAimController.h"
#include "BoxController.h"
#include "MetaCapsuleController.h"
#include "BlastHornetController.h"
#include "BlastHornetChildController.h"
#include "BlastHornetChild2Controller.h"
#include "BlastHornetBulletController.h"
#include "ShurikeinController.h"
#include "AudioSource.h"

#pragma comment(lib, "Framework.lib")

using namespace Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	srand(time(0));
	CGameManager::Instantiate(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN);
	CGameManager* pGameManager = CGameManager::GetInstance();

	CScene* pScene = new CScene("Main Scene", {8000,8000});
	pGameManager->SetCurrentScene(pScene);
	pGameManager->SetIsDebugging(false);
	CGameObject* pMainCamera = pScene->GetMainCamera();
	pMainCamera->GetComponent<CTransform>()->Set_Position(Vector2(128, 896));
	pMainCamera->AddComponent<CameraController>()->SetIsFree(false);
	pMainCamera->GetComponent<CCamera>()->SetScale({ 2,2 })->SetSize({ SCREEN_WIDTH,SCREEN_HEIGHT });


	CResourceManager *pResourceManager = CResourceManager::GetInstance();
	pResourceManager->AddTexture(Texture_MegaManX, ".\\Resources\\Player\\MegaManXEdited.png", NULL, ".\\Resources\\Player\\MegaManXEdited.xml");
	pResourceManager->AddTexture(Texture_MegaManX_Dash, ".\\Resources\\Player\\MegaManX-Dash.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture(Texture_MegaManX_Dash_Shoot, ".\\Resources\\Player\\MegaManX-Dash Shoot.png", NULL, ".\\Resources\\Player\\MegaManX-Dash.xml");
	pResourceManager->AddTexture(Texture_MegaManX_Power, ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.png", NULL, ".\\Resources\\Player\\SNES_-_Mega_Man_X3_-_Zero.xml");
	pResourceManager->AddTexture(Texture_X3_Specific, ".\\Resources\\Player\\X3-Specific.png", NULL, ".\\Resources\\Player\\X3-Specific.xml");
	pResourceManager->AddTexture(Texture_MegaManX_Effect, ".\\Resources\\Player\\MegaManX-Effect.png", D3DCOLOR_XRGB(64,102,232), ".\\Resources\\Player\\MegaManX-Effect.xml");
	pResourceManager->AddTexture(Texture_MegaManX_Explosions_Effect, ".\\Resources\\Enemies\\x3_explosions.png", COLOR_WHITE, ".\\Resources\\Enemies\\x3_explosions.xml");
	pResourceManager->AddTexture(Texture_Map_Objects, ".\\Resources\\Map\\Objects.png", NULL, ".\\Resources\\Map\\Objects.xml");
	pResourceManager->AddTexture(Texture_Map, ".\\Resources\\Map\\Map.png", NULL, ".\\Resources\\Map\\Map.xml");
	pResourceManager->AddTexture(Texture_WeaponsAndItems, ".\\Resources\\Weapons and Items\\Weapons and Items.png", NULL, ".\\Resources\\Weapons and Items\\Weapons and Items.xml");
	pResourceManager->AddTexture(Texture_EnemiesAndBosses, ".\\Resources\\Enemies\\enemies_and_bosses.png", NULL, ".\\Resources\\Enemies\\enemies_and_bosses.xml");
	pResourceManager->AddTexture(Texture_Door, ".\\Resources\\Map\\Door.png", NULL, ".\\Resources\\Map\\Door.xml", VECTOR2_ZERO);
	pResourceManager->AddTexture(Texture_Health_Bar, ".\\Resources\\UI\\Health_Bar.png", NULL, ".\\Resources\\UI\\Health_Bar.xml", {0,1}); 
	pResourceManager->AddTexture(Texture_Blast_Hornet, ".\\Resources\\Blast Hornet\\sprites.png", NULL, ".\\Resources\\Blast Hornet\\sprites.xml");

	pResourceManager->AddSound(AUDIO_SOUND_TRACK, ".\\Resources\\Sounds\\BlastHornetSoundTrack.wav")
		->AddSound(AUDIO_MEGAMAN_SHOOT, ".\\Resources\\Sounds\\SE_0A.wav")
		->AddSound(AUDIO_MEGAMAN_POWER_SHOOT, ".\\Resources\\Sounds\\SE_3A.wav");

	//From file MegaManXEdited.png
	new CAnimation(Animation_MegaManX_Init, Texture_MegaManX, 0, 2, 1000, false);
	new CAnimation(Animation_MegaManX_InitLand, Texture_MegaManX, 2, 6, 100, false);
	CAnimation* anim = new CAnimation(Animation_MegaManX_Idle, Texture_MegaManX, 8, 2, 100, true);
	anim->Add(Texture_MegaManX, 7, 1, 2000);
	anim = new CAnimation(Animation_MegaManX_Idle_Shoot, Texture_MegaManX, 10, 3, 120, false);
	anim->Add(Texture_MegaManX, 11)->Add(Texture_MegaManX, 10);
	new CAnimation(Animation_MegaManX_Run, Texture_MegaManX, 14, 10, 100, true);
	new CAnimation(Animation_MegaManX_Run_Shoot, Texture_MegaManX, 24, 10, 100, true);
	new CAnimation(Animation_MegaManX_Fall, Texture_MegaManX, 37, 2, 120, false);
	new CAnimation(Animation_MegaManX_Fall_Shoot, Texture_MegaManX, 44, 2, 120, false);
	new CAnimation(Animation_MegaManX_Landfall, Texture_MegaManX, 39, 1, 120, false);
	new CAnimation(Animation_MegaManX_Landfall_Shoot, Texture_MegaManX, 46, 1, 120, false);
	new CAnimation(Animation_MegaManX_Jump, Texture_MegaManX, 34, 3, 100, false);
	new CAnimation(Animation_MegaManX_Jump_Shoot, Texture_MegaManX, 41, 3, 100, false);
	new CAnimation(Animation_MegaManX_Wall_Clinging, Texture_MegaManX, 50, 1, 120, true);
	new CAnimation(Animation_MegaManX_Wall_Clinging_Shoot, Texture_MegaManX, 55, 2, 120, true);
	anim = new CAnimation(Animation_MegaManX_WasHit, Texture_MegaManX, 89, 3, 100, false);
	anim->Add(Texture_MegaManX, 90)->Add(Texture_MegaManX, 91)->Add(Texture_MegaManX, 90)->Add(Texture_MegaManX, 91);

	new CAnimation(Animation_MegaManX_Idle_Cut, Texture_X3_Specific, 53, 11, 50, false);
	new CAnimation(Animation_MegaManX_Jump_Cut, Texture_X3_Specific, 64, 11, 50, false);
	new CAnimation(Animation_MegaManX_Sky_Walk, Texture_X3_Specific, 20, 4, 100, false);

	//From file MegaManX-Dash Shoot.png
	anim = new CAnimation(Animation_MegaManX_Dash, Texture_MegaManX, 81, 1, 100, false);
	anim->Add(Texture_MegaManX, 82, -1, 400);
	anim = new CAnimation(Animation_MegaManX_Dash_Shoot, Texture_MegaManX, 83, 1, 100, false);
	anim->Add(Texture_MegaManX, 84, -1, 400);

	//From file SNES_-_Mega_Man_X3_-_Zero.png
	new CAnimation(Animation_Effect_Die, Texture_MegaManX_Power, 0, 17, 30, true);

	//From file Map/Objects.png
	new CAnimation(Animation_MapBehind_1, Texture_Map_Objects, 32, 9, 100, true);
	new CAnimation(Animation_Machine_1_Run, Texture_Map_Objects, 28, 3, 50, true);
	new CAnimation(Animation_Machine_1_Idle, Texture_Map_Objects, 28, 1, 50, true);

	//Animation Effect
	new CAnimation(Animation_Effect_BluePower, Texture_MegaManX_Effect, 0, 11, 50, true);
	new CAnimation(Animation_Effect_OrangePower, Texture_MegaManX_Effect, 11, 11, 50, true);
	anim = new CAnimation(Animation_Effect_Dash, Texture_MegaManX_Effect, 22, 8, 70, true);
	{
		auto frames = anim->GetFrames();
		for (CAnimation::SFrame frame : frames)
		{
			frame.m_sprite->SetAnchor({ 0,1 });
		}
	}
	anim = new CAnimation(Animation_Effect_SmokeDash, Texture_MegaManX_Effect, 30, 12, 30, true);
	{
		auto frames = anim->GetFrames();
		for (CAnimation::SFrame frame : frames)
		{
			frame.m_sprite->SetAnchor({ 0.5,1 });
		}
	}
	new CAnimation(Animation_Effect_DoubleJump, Texture_MegaManX_Effect, 42, 1, 50, true);
	new CAnimation(Animation_Effect_Smoke, Texture_MegaManX_Effect, 43, 6, 50, true);

	anim = new CAnimation(Animation_Effect_Explode, Texture_MegaManX_Explosions_Effect, 0, 6, 100, false);
	anim->Add(Texture_MegaManX_Explosions_Effect, 0, 2);
	anim = new CAnimation(Animation_Effect_Explode_Blue, Texture_MegaManX_Explosions_Effect, 6, 6, 100, false);
	anim->Add(Texture_MegaManX_Explosions_Effect, 6, 2);

	// Effect Prefabs
	{
		auto effectPool = EffectPool::GetInstance();
		CGameObject* pPrefab = pResourceManager->AddPrefab(Prefab_Effect_Dash);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-1);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_Dash);
		pPrefab->AddComponent<EffectAutoRemove>();

		pPrefab = pResourceManager->AddPrefab(Prefab_Effect_DoubleJump);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-20);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_DoubleJump);
		pPrefab->AddComponent<EffectAutoRemove>();

		pPrefab = pResourceManager->AddPrefab(Prefab_Effect_Smoke);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-20);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_Smoke);
		pPrefab->AddComponent<EffectAutoRemove>();

		pPrefab = pResourceManager->AddPrefab(Prefab_Effect_SmokeDash);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-20);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_SmokeDash);
		pPrefab->AddComponent<EffectAutoRemove>();

		pPrefab = pResourceManager->AddPrefab(Prefab_Effect_Explode);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-20);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_Explode);
		pPrefab->AddComponent<EffectAutoRemove>();

		pPrefab = pResourceManager->AddPrefab(Prefab_Effect_Explode_Blue);
		pPrefab->AddComponent<CRenderer>()->SetZOrder(-20);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Effect_Explode_Blue);
		pPrefab->AddComponent<EffectAutoRemove>();

		effectPool->AddNewEffect(Prefab_Effect_Smoke);
		effectPool->AddNewEffect(Prefab_Effect_SmokeDash);
		effectPool->AddNewEffect(Prefab_Effect_Explode);
		effectPool->AddNewEffect(Prefab_Effect_Explode_Blue);
	}

	//Bullet Prefabs
	{
		auto bulletPool = BulletPool::GetInstance();
		// Head Gunner Bullet
		{
			new CAnimation(Animation_HeadGunner_Bullet, Texture_EnemiesAndBosses, 53, 2, 100, true);
			auto pBullet = pResourceManager->AddPrefab(Prefab_BusterShot_Bullet);
			pBullet->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 53);
			pBullet->AddComponent<CAnimator>()
				->AddAnimation(Animation_HeadGunner_Bullet);
			pBullet->AddComponent<CRigidbody>()->SetGravityScale(0);
			pBullet->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			pBullet->AddComponent<BulletController>();
			pBullet->AddComponent<CanAttacked>()->InitDamage(10);

			bulletPool->AddNewTypeBullet(Prefab_BusterShot_Bullet);
		}

		// Notor Banger Bullet
		{
			auto pBullet = pResourceManager->AddPrefab(Prefab_NotorBanger_Bullet);
			pBullet->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 111);
			pBullet->AddComponent<CRigidbody>()->SetGravityScale(1);
			pBullet->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			pBullet->AddComponent<BulletController>();
			pBullet->AddComponent<CanAttacked>()->InitDamage(20);

			bulletPool->AddNewTypeBullet(Prefab_NotorBanger_Bullet);
		}


		//Buster Shots
		{
			new CAnimation(Animation_BusterShot_Bullet_Init, Texture_WeaponsAndItems, 0, 1, 100, false);
			new CAnimation(Animation_BusterShot_Bullet_Explosive, Texture_WeaponsAndItems, 1, 3, 100, false);
			auto pBusterBullet = pResourceManager->AddPrefab(Prefab_BusterShot);
			pBusterBullet->AddComponent<CAnimator>()
				->AddAnimation(Animation_BusterShot_Bullet_Init)
				->AddAnimation(Animation_BusterShot_Bullet_Explosive)
				->AddBool(Bool_IsCollision, false)
				->AddTransition(Animation_BusterShot_Bullet_Init, Animation_BusterShot_Bullet_Explosive, true, Bool_IsCollision, true);
			pBusterBullet->GetComponent<CRenderer>()->SetZOrder(-10);
			pBusterBullet->AddComponent<CRigidbody>()->SetGravityScale(0);
			pBusterBullet->AddComponent<CBoxCollider>()->SetSize({ 1,1 })->SetIsTrigger(true);
			pBusterBullet->AddComponent<BusterShotController>();
			pBusterBullet->AddComponent<CanAttacked>()->InitDamage(20);

			bulletPool->AddNewTypeBullet(Prefab_BusterShot);
		}
	}

	// Notor Banger Animation
	{
		new CAnimation(Animation_Notor_Banger_Idle, Texture_EnemiesAndBosses, 98, 1, 100, true);
		new CAnimation(Animation_Notor_Banger_Jump, Texture_EnemiesAndBosses, 99, 3, 100, false);

		new CAnimation(Animation_Notor_Banger_0, Texture_EnemiesAndBosses, 106, 1);
		new CAnimation(Animation_Notor_Banger_30, Texture_EnemiesAndBosses, 107, 1);
		new CAnimation(Animation_Notor_Banger_45, Texture_EnemiesAndBosses, 108, 1);
		new CAnimation(Animation_Notor_Banger_60, Texture_EnemiesAndBosses, 109, 1);
		new CAnimation(Animation_Notor_Banger_90, Texture_EnemiesAndBosses, 110, 1);
	}

	//Door
	{
		new CAnimation(Animation_Door1_Close, Texture_Door, 0, 9, 50, false);
		new CAnimation(Animation_Door2_Close, Texture_Door, 9, 17, 50, false);
		auto tmp = new CAnimation(Animation_Door1_Open, Texture_Door, 8, 1, 50, false);
		for (int i = 7; i >= 0; --i)
		{
			tmp->Add(Texture_Door, i);
		}
		tmp = new CAnimation(Animation_Door2_Open, Texture_Door, 25, 1, 50, false);
		for(int i=24;i>=9;--i)
		{
			tmp->Add(Texture_Door, i);
		}

		//Prefabs
		auto pPrefab = pResourceManager->AddPrefab(Prefab_Door1);
		pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_Door, 0);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Door1_Close)
			->AddAnimation(Animation_Door1_Open)
			->AddBool(Bool_IsOpen, false)
			->AddTransition(Animation_Door1_Close, Animation_Door1_Open, false, Bool_IsOpen, true)
			->AddTransition(Animation_Door1_Open, Animation_Door1_Close, false, Bool_IsOpen, false);
		pPrefab->AddComponent<CRigidbody>()->SetIsKinematic(true)->SetNeedUpdate(true);
		pPrefab->AddComponent<CBoxCollider>()->SetIsTrigger(true);
		pPrefab->AddComponent<DoorController>();


		pPrefab = pResourceManager->AddPrefab(Prefab_Door2);
		pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_Door, 0);
		pPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Door2_Close)
			->AddAnimation(Animation_Door2_Open)
			->AddBool(Bool_IsOpen, false)
			->AddTransition(Animation_Door2_Close, Animation_Door2_Open, false, Bool_IsOpen, true)
			->AddTransition(Animation_Door2_Open, Animation_Door2_Close, false, Bool_IsOpen, false);
		pPrefab->AddComponent<CRigidbody>()->SetIsKinematic(true)->SetNeedUpdate(true);
		pPrefab->AddComponent<CBoxCollider>()->SetIsTrigger(true);
		pPrefab->AddComponent<DoorController>();
	}

	//Carry Aim Prefabs
	{
		anim = new CAnimation(Animation_Carry_Aim_Fly, Texture_EnemiesAndBosses, 8, 4, 80, true); 
		{
			auto frames = anim->GetFrames();
			for (CAnimation::SFrame frame : frames)
			{
				frame.m_sprite->SetAnchor({ 0.5,0 });
			}
		}
		anim = new CAnimation(Animation_Carry_Aim_Fly_Explode, Texture_EnemiesAndBosses, 12, 4, 80, true);
		{
			auto frames = anim->GetFrames();
			for (CAnimation::SFrame frame : frames)
			{
				frame.m_sprite->SetAnchor({ 0.5,0 });
			}
		}

		CGameObject* pCarryAimPrefab = pResourceManager->AddPrefab(Prefab_Carry_Aim);
		pCarryAimPrefab->AddComponent<CRenderer>()->SetZOrder(-10)->SetSprite(Texture_EnemiesAndBosses, 8);
		pCarryAimPrefab->AddComponent<CAnimator>()
			->AddAnimation(Animation_Carry_Aim_Fly)
			->AddAnimation(Animation_Carry_Aim_Fly_Explode)
			->AddBool(Bool_IsCollision, false)
			->AddTransition(Animation_Carry_Aim_Fly, Animation_Carry_Aim_Fly_Explode, true, Bool_IsCollision, true, true)
		;
		pCarryAimPrefab->AddComponent<CRigidbody>()->SetGravityScale(0);
		pCarryAimPrefab->AddComponent<CBoxCollider>()->SetIsTrigger(true);
		pCarryAimPrefab->GetComponent<CBoxCollider>()->SetAnchor({0.5,0});
		pCarryAimPrefab->AddComponent<CarryAimController>();
		pCarryAimPrefab->AddComponent<CanBeAttacked>()->InitHealth(40);
		pCarryAimPrefab->SetIsActive(false);
	}

	//Box Prefab
	{
		CGameObject* pBoxPrefab = pResourceManager->AddPrefab(Prefab_Box);
		pBoxPrefab->AddComponent<CRenderer>()->SetZOrder(-10)->SetSprite(Texture_EnemiesAndBosses, 2);
		pBoxPrefab->AddComponent<CRigidbody>()->SetGravityScale(0);
		pBoxPrefab->AddComponent<CBoxCollider>()->SetIsTrigger(true);
		pBoxPrefab->AddComponent<BoxController>();
		pBoxPrefab->AddComponent<CanBeAttacked>()->InitHealth(20);
	}

	auto pMapBehindPrefab = pResourceManager->AddPrefab(Prefab_MapBehind_1);
	pMapBehindPrefab->AddComponent<CAnimator>()->AddAnimation(Animation_MapBehind_1);

	// Notor Banger Prefab
	{
		// Prefab
		{
			std::string animationNames[] = { Animation_Notor_Banger_Idle, Animation_Notor_Banger_Jump, Animation_Notor_Banger_0, Animation_Notor_Banger_30,
				Animation_Notor_Banger_45, Animation_Notor_Banger_60, Animation_Notor_Banger_90 };

			std::string boolNames[] = { Bool_IsIdle, Bool_IsJump, Bool_Is0, Bool_Is30, Bool_Is45, Bool_Is60, Bool_Is90 };

			auto pPrefab = pResourceManager->AddPrefab(Prefab_NotorBanger);
			pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 98);
			pPrefab->AddComponent<CAnimator>()
				->AddAnimation(Animation_Notor_Banger_Idle)
				->AddAnimation(Animation_Notor_Banger_Jump)
				->AddAnimation(Animation_Notor_Banger_0)
				->AddAnimation(Animation_Notor_Banger_30)
				->AddAnimation(Animation_Notor_Banger_45)
				->AddAnimation(Animation_Notor_Banger_60)
				->AddAnimation(Animation_Notor_Banger_90)

				->AddBool(Bool_IsIdle, true)
				->AddBool(Bool_IsJump, false)
				->AddBool(Bool_Is0, false)
				->AddBool(Bool_Is30, false)
				->AddBool(Bool_Is45, false)
				->AddBool(Bool_Is60, false)
				->AddBool(Bool_Is90, false)

				->AddTransition(Animation_Notor_Banger_Idle, Animation_Notor_Banger_Jump, false, Bool_IsJump, true)
				->AddTransition(Animation_Notor_Banger_Jump, Animation_Notor_Banger_Idle, true, Bool_IsIdle, true);

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

	// Head Gunner Prefab
	{
		// Animations
		{
			new CAnimation(Animation_HeadGunner_Idle, Texture_EnemiesAndBosses, 45, 1, 200, false);
			new CAnimation(Animation_HeadGunner_Shoot_1, Texture_EnemiesAndBosses, 46, 3, 200, false);
			new CAnimation(Animation_HeadGunner_Shoot_2, Texture_EnemiesAndBosses, 49, 3, 200, false);
			new CAnimation(Animation_HeadGunner_End, Texture_EnemiesAndBosses, 52, 1, 200, false);
		}

		// Prefab
		{

			auto pPrefab = pResourceManager->AddPrefab(Prefab_HeadGunner);
			pPrefab->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 45);
			pPrefab->AddComponent<CAnimator>()
				->AddAnimation(Animation_HeadGunner_Idle)
				->AddAnimation(Animation_HeadGunner_Shoot_1)
				->AddAnimation(Animation_HeadGunner_Shoot_2)
				->AddAnimation(Animation_HeadGunner_End)


				->AddBool(Bool_IsShoot, false)

				->AddTransition(Animation_HeadGunner_Idle, Animation_HeadGunner_Shoot_1, true, Bool_IsShoot, true)
				->AddTransition(Animation_HeadGunner_Shoot_1, Animation_HeadGunner_Shoot_2, true, Bool_IsShoot, true)
				->AddTransition(Animation_HeadGunner_Shoot_2, Animation_HeadGunner_End, true)
				->AddTransition(Animation_HeadGunner_End, Animation_HeadGunner_Idle, true)
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

	//MetaCapsule prefab
	CGameObject* pMetaCapsule = pResourceManager->AddPrefab(Prefab_MetaCapsule);
	{
		anim = new CAnimation(Animation_MetaCapsule_Open, Texture_EnemiesAndBosses, 76, 19, 100, false);
		{
			auto frames = anim->GetFrames();
			for (CAnimation::SFrame frame : frames)
			{
				frame.m_sprite->SetAnchor({ 0,0 });
			}
		}
		anim = new CAnimation(Animation_MetaCapsule_Close, Texture_EnemiesAndBosses, 94, 1, 100, false);
		{
			for (int i = 93; i >= 76; --i)
			{
				anim->Add(Texture_EnemiesAndBosses, i);
			}

			auto frames = anim->GetFrames();
			for (CAnimation::SFrame frame : frames)
			{
				frame.m_sprite->SetAnchor({ 0,0 });
			}
		}
		new CAnimation(Animation_MetaCapsule_Bullet, Texture_EnemiesAndBosses, 95, 3, 100, true);

		pMetaCapsule->AddComponent<CRenderer>()->SetZOrder(-6);
		pMetaCapsule->AddComponent<CAnimator>()
			->AddAnimation(Animation_MetaCapsule_Open)
			->AddAnimation(Animation_MetaCapsule_Close)
			->AddBool(Bool_IsOpen, true)
			->AddTransition(Animation_MetaCapsule_Close, Animation_MetaCapsule_Open, false, Bool_IsOpen, true)
			->AddTransition(Animation_MetaCapsule_Open, Animation_MetaCapsule_Close, false, Bool_IsOpen, false)
			;
		pMetaCapsule->AddComponent<CRigidbody>()->SetGravityScale(0);
		pMetaCapsule->AddComponent<CBoxCollider>()->SetSize({32,30})->SetAnchor({0,0});
		pMetaCapsule->GetComponent<CBoxCollider>()->SetIsTrigger(true);
		pMetaCapsule->GetComponent<CBoxCollider>()->SetIsActive(false);
		pMetaCapsule->AddComponent<MetaCapsuleController>();
		pMetaCapsule->AddComponent<CanBeAttacked>()->InitHealth(40);
		pMetaCapsule->SetIsActive(false);

		CGameObject* pMetaCapsuleBullet = pResourceManager->AddPrefab(Prefab_MetaCapsule_Bullet);
		{
			pMetaCapsuleBullet->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 95);
			pMetaCapsuleBullet->AddComponent<CAnimator>()->AddAnimation(Animation_MetaCapsule_Bullet);
			pMetaCapsuleBullet->AddComponent<CRigidbody>()->SetGravityScale(0);
			pMetaCapsuleBullet->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			pMetaCapsuleBullet->AddComponent<BulletController>();
			pMetaCapsuleBullet->AddComponent<CanAttacked>()->InitDamage(25);
			pMetaCapsuleBullet->SetIsActive(false);
		}
	}

	do
	{
		//Player
		CGameObject* pPlayer = new CGameObject("Player", { 2160, 1129 });//2160, 1129 Suriken || 45, 875 Start || 4370, 1100 Building || 7720, 1827 Blast
		{
			pPlayer->AddComponent<CAnimator>()
				->AddAnimation(Animation_MegaManX_Init)
				->AddAnimation(Animation_MegaManX_InitLand)
				->AddAnimation(Animation_MegaManX_Idle)
				->AddAnimation(Animation_MegaManX_Idle_Shoot)
				->AddAnimation(Animation_MegaManX_Jump)
				->AddAnimation(Animation_MegaManX_Jump_Shoot)
				->AddAnimation(Animation_MegaManX_Fall)
				->AddAnimation(Animation_MegaManX_Fall_Shoot)
				->AddAnimation(Animation_MegaManX_Landfall)
				->AddAnimation(Animation_MegaManX_Landfall_Shoot)
				->AddAnimation(Animation_MegaManX_Run)
				->AddAnimation(Animation_MegaManX_Dash)
				->AddAnimation(Animation_MegaManX_Run_Shoot)
				->AddAnimation(Animation_MegaManX_Dash_Shoot)
				->AddAnimation(Animation_MegaManX_Wall_Clinging)
				->AddAnimation(Animation_MegaManX_Wall_Clinging_Shoot)
				->AddAnimation(Animation_MegaManX_Idle_Cut)
				->AddAnimation(Animation_MegaManX_Jump_Cut)
				->AddAnimation(Animation_MegaManX_Sky_Walk)
				->AddAnimation(Animation_MegaManX_WasHit)

				->AddBool(Bool_IsIdle, false)
				->AddBool(Bool_IsJump, false)
				->AddBool(Bool_IsFall, false)
				->AddBool(Bool_IsLandFall, false)
				->AddBool(Bool_IsShoot, false)
				->AddBool(Bool_IsRun, false)
				->AddBool(Bool_IsDash, false)
				->AddBool(Bool_IsClinging, false)
				->AddBool(Bool_IsSkyWalk, false)
				->AddBool(Bool_IsCut, false)
				->AddBool(Bool_IsWasHit, false)

				->AddTransition(Animation_MegaManX_Init, Animation_MegaManX_InitLand, true, Bool_IsLandFall, true)
				->AddTransition(Animation_MegaManX_InitLand, Animation_MegaManX_Idle)

				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Dash, true, Bool_IsDash, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Jump, true, Bool_IsJump, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Fall, true, Bool_IsFall, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Run, true, Bool_IsRun, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Idle_Shoot, true, Bool_IsShoot, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_Idle_Cut, true, Bool_IsCut, true)
				->AddTransition(Animation_MegaManX_Idle, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_Idle)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_Dash, true, Bool_IsDash, true)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_Jump, true, Bool_IsJump, true)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_Fall, true, Bool_IsFall, true)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_Run, true, Bool_IsRun, true)
				->AddTransition(Animation_MegaManX_Idle_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Dash, Animation_MegaManX_Idle, false, Bool_IsDash, false)
				->AddTransition(Animation_MegaManX_Dash, Animation_MegaManX_Dash_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Dash, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Dash_Shoot, Animation_MegaManX_Dash, true, Bool_IsShoot, false, true)
				->AddTransition(Animation_MegaManX_Dash_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Jump, Animation_MegaManX_Fall, true, Bool_IsFall, true)
				->AddTransition(Animation_MegaManX_Jump, Animation_MegaManX_Wall_Clinging, true, Bool_IsClinging, true)
				->AddTransition(Animation_MegaManX_Jump, Animation_MegaManX_Jump_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Jump, Animation_MegaManX_Sky_Walk, true, Bool_IsSkyWalk, true, true)
				->AddTransition(Animation_MegaManX_Jump, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Jump_Shoot, Animation_MegaManX_Jump, true, Bool_IsShoot, false, true)
				->AddTransition(Animation_MegaManX_Jump_Shoot, Animation_MegaManX_Fall, true, Bool_IsFall, true)
				->AddTransition(Animation_MegaManX_Jump_Shoot, Animation_MegaManX_Wall_Clinging, true, Bool_IsClinging, true)
				->AddTransition(Animation_MegaManX_Jump_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Sky_Walk, Animation_MegaManX_Fall, true, Bool_IsFall, true)

				->AddTransition(Animation_MegaManX_Fall, Animation_MegaManX_Landfall, true, Bool_IsLandFall, true)
				->AddTransition(Animation_MegaManX_Fall, Animation_MegaManX_Fall_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Fall, Animation_MegaManX_Wall_Clinging, true, Bool_IsClinging, true)
				->AddTransition(Animation_MegaManX_Fall, Animation_MegaManX_Sky_Walk, true, Bool_IsSkyWalk, true)
				->AddTransition(Animation_MegaManX_Fall, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Fall_Shoot, Animation_MegaManX_Fall, true, Bool_IsShoot, false, true)
				->AddTransition(Animation_MegaManX_Fall_Shoot, Animation_MegaManX_Landfall, true, Bool_IsLandFall, true)
				->AddTransition(Animation_MegaManX_Fall_Shoot, Animation_MegaManX_Wall_Clinging, true, Bool_IsClinging, true)
				->AddTransition(Animation_MegaManX_Fall_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Landfall, Animation_MegaManX_Idle)
				->AddTransition(Animation_MegaManX_Landfall, Animation_MegaManX_Landfall_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Landfall, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Landfall_Shoot, Animation_MegaManX_Landfall, true, Bool_IsShoot, false, true)
				->AddTransition(Animation_MegaManX_Landfall_Shoot, Animation_MegaManX_Idle)
				->AddTransition(Animation_MegaManX_Landfall_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Run, Animation_MegaManX_Idle, true, Bool_IsRun, false)
				->AddTransition(Animation_MegaManX_Run, Animation_MegaManX_Jump, true, Bool_IsJump, true)
				->AddTransition(Animation_MegaManX_Run, Animation_MegaManX_Dash, true, Bool_IsDash, true)
				->AddTransition(Animation_MegaManX_Run, Animation_MegaManX_Run_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Run, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Run_Shoot, Animation_MegaManX_Run, true, Bool_IsShoot, false, true)
				->AddTransition(Animation_MegaManX_Run_Shoot, Animation_MegaManX_Idle, true, Bool_IsRun, false)
				->AddTransition(Animation_MegaManX_Run_Shoot, Animation_MegaManX_Jump, true, Bool_IsJump, true)
				->AddTransition(Animation_MegaManX_Run_Shoot, Animation_MegaManX_Dash, true, Bool_IsDash, true)
				->AddTransition(Animation_MegaManX_Run_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_Wall_Clinging, Animation_MegaManX_Idle, true, Bool_IsClinging, false)
				//->AddTransition(Animation_MegaManX_Wall_Clinging, Animation_MegaManX_Jump, true, Bool_IsJump, true)
				->AddTransition(Animation_MegaManX_Wall_Clinging, Animation_MegaManX_Wall_Clinging_Shoot, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Wall_Clinging, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)
				->AddTransition(Animation_MegaManX_Wall_Clinging_Shoot, Animation_MegaManX_Wall_Clinging, true, Bool_IsShoot, true, true)
				->AddTransition(Animation_MegaManX_Wall_Clinging_Shoot, Animation_MegaManX_WasHit, true, Bool_IsWasHit, true)

				->AddTransition(Animation_MegaManX_WasHit, Animation_MegaManX_Idle)

				->AddTransition(Animation_MegaManX_Idle_Cut, Animation_MegaManX_Idle, false, Bool_IsCut, false)
				->AddTransition(Animation_MegaManX_Idle_Cut, Animation_MegaManX_Jump_Cut, true, Bool_IsJump, true, true)
				->AddTransition(Animation_MegaManX_Jump_Cut, Animation_MegaManX_Idle_Cut, true, Bool_IsJump, false, true)
				->AddTransition(Animation_MegaManX_Jump_Cut, Animation_MegaManX_Jump, false, Bool_IsCut, false)
				;
			pPlayer->GetComponent<CRenderer>()->SetFlipY(false);
			pPlayer->AddComponent<CRigidbody>()->SetVelocity(Vector2(0, 0));
			pPlayer->GetComponent<CRigidbody>()->SetGravityScale(1);
			pPlayer->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pPlayer->GetComponent<CBoxCollider>()->SetSize(Vector2(30, 34));
			pPlayer->GetComponent<CBoxCollider>()->SetAutoBoundSize(false);
			pPlayer->AddComponent<PlayerController>()->SetSpeed(0.1);
			pPlayer->AddComponent<CanBeAttacked>()->InitHealth(1000); 
			pPlayer->AddComponent<CAudioSource>();
			pPlayer->GetComponent<CAudioSource>()->AddSound(AUDIO_SOUND_TRACK, true);// ->Play(AUDIO_SOUND_TRACK);
			pPlayer->GetComponent<CAudioSource>()->AddSound(AUDIO_MEGAMAN_SHOOT, false);
			pPlayer->GetComponent<CAudioSource>()->AddSound(AUDIO_MEGAMAN_POWER_SHOOT, false);

			CGameObject* pPowerEffect = new CGameObject("Power Effect");
			pPowerEffect->SetIsActive(false);
			pPowerEffect->GetComponent<CTransform>()->SetParent(pPlayer)->Set_Position({ 0,0 }, false);
			pPowerEffect->AddComponent<CRenderer>()->SetZOrder(-1);
			pPowerEffect->AddComponent<CAnimator>()
				->AddAnimation(Animation_Effect_Dash);
			pPlayer->GetComponent<PlayerController>()->m_Power = pPowerEffect;

			CGameObject* pDieEffect = new CGameObject("Die Effect");
			pDieEffect->SetIsActive(false);
			pDieEffect->GetComponent<CTransform>()->SetParent(pPlayer)->Set_Position({ 0,0 }, false);
			pDieEffect->AddComponent<CRenderer>()->SetZOrder(-1);
			pDieEffect->AddComponent<CAnimator>()
				->AddAnimation(Animation_Effect_Die);
			pPlayer->GetComponent<PlayerController>()->m_DieEffect = pDieEffect;

			CGameObject* pDashFullEffect = new CGameObject("Dash Full Effect");
			pDashFullEffect->GetComponent<CTransform>()->SetParent(pPlayer)->Set_Position({ 0,17 }, false);
			pDashFullEffect->AddComponent<DashFullEffect>();
			pPlayer->GetComponent<PlayerController>()->m_DashFullEffectEffect = pDashFullEffect;
		}

		CGameObject* pBackground = new CGameObject("Map");
		pBackground->AddComponent<CRenderer>()->SetSprite(Texture_Map)
			->SetZOrder(10)->SetAnchor(VECTOR2_ZERO);
		{
			//Object Prefabs
			CGameObject* pPrefabs = pResourceManager->AddPrefab(Prefab_Ladder1);
			pPrefabs->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 15)->SetAnchor({0,0});

			pPrefabs = pResourceManager->AddPrefab(Prefab_Ladder2);
			pPrefabs->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 16)->SetAnchor({ 0,0 });

			pPrefabs = pResourceManager->AddPrefab(Prefab_BrokenWall_Left);
			pPrefabs->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 0)->SetAnchor({ 0,0 });

			pPrefabs = pResourceManager->AddPrefab(Prefab_BrokenWall_Right);
			pPrefabs->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 1)->SetAnchor({ 0,0 });

			//Ground
			for (int i = 31; i < 31 + 40; ++i)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite(Texture_Map, i)->GetSourceRect();

				CGameObject* pGround = new CGameObject("Ground" + std::to_string(i-13));
				pGround->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pGround->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pGround->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}

			//Ceiling
			for (int i = 0; i < 0 + 27; ++i)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite(Texture_Map, i)->GetSourceRect();

				CGameObject* pCeiling = new CGameObject("Ceiling" + std::to_string(i));
				pCeiling->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pCeiling->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pCeiling->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}

			//Wall
			for (int i = 71; i < 71 + 26; ++i)
			{
				Rect spriteRect = CResourceManager::GetInstance()->GetSprite(Texture_Map, i)->GetSourceRect();

				CGameObject* pWall = new CGameObject("Wall" + std::to_string(i-38));
				pWall->GetComponent<CTransform>()->SetParent(pBackground)->Set_Position({ spriteRect.left, spriteRect.top }, false);
				pWall->AddComponent<CRigidbody>()->SetIsKinematic(true);
				pWall->AddComponent<CBoxCollider>()->SetSize(spriteRect.Size())->SetAnchor({ 0,0 });
			}

			//Ladder
			CGameObject::Instantiate(Prefab_Ladder2, pBackground, { 2640,1134 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_Ladder2, pBackground, { 2800,1134 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_Ladder2, pBackground, { 5440,1134 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_Ladder2, pBackground, { 5536,1134 })->GetComponent<CRenderer>()->SetZOrder(-10);
			
			CGameObject::Instantiate(Prefab_Ladder1, pBackground, { 5440,768 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_Ladder1, pBackground, { 5536,768 })->GetComponent<CRenderer>()->SetZOrder(-10);

			//Broken Wall
			CGameObject::Instantiate(Prefab_BrokenWall_Left, pBackground, { 3520,1104 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_BrokenWall_Left, pBackground, { 3968,1104 })->GetComponent<CRenderer>()->SetZOrder(-10);
			
			CGameObject::Instantiate(Prefab_BrokenWall_Right, pBackground, { 3295,1104 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_BrokenWall_Right, pBackground, { 3743,1104 })->GetComponent<CRenderer>()->SetZOrder(-10);
			CGameObject::Instantiate(Prefab_BrokenWall_Right, pBackground, { 4191,1104 })->GetComponent<CRenderer>()->SetZOrder(-10);

			//Broken Box
			CGameObject* pTwoBox = new CGameObject("TwoBox");
			pTwoBox->GetComponent<CTransform>()->Set_Position({ 3392, 944 });
			pTwoBox->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 56)->SetAnchor({0,0});
			pTwoBox->AddComponent<CRigidbody>()->SetIsKinematic(true);
			pTwoBox->AddComponent<CBoxCollider>()->SetAnchor({0,0});

			CGameObject* pRoofBrokenBoxs = new CGameObject("RoofBrokenBoxs");
			pRoofBrokenBoxs->GetComponent<CTransform>()->Set_Position({ 3840, 944 });
			pRoofBrokenBoxs->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 42)->SetAnchor({ 0,0 });
			pRoofBrokenBoxs->AddComponent<CRigidbody>()->SetIsKinematic(true);
			pRoofBrokenBoxs->AddComponent<CBoxCollider>()->SetAnchor({ 0,0 });

			//Door
			CGameObject::Instantiate(Prefab_Door2, pBackground, { 2303,1153 });
			CGameObject::Instantiate(Prefab_Door2, pBackground, { 2544,1153 });
			CGameObject::Instantiate(Prefab_Door2, pBackground, { 5632,1152 });
			CGameObject::Instantiate(Prefab_Door2, pBackground, { 5872,1152 });

			CGameObject::Instantiate(Prefab_Door1, pBackground, { 7391,1920 });
			CGameObject::Instantiate(Prefab_Door1, pBackground, { 7680,1920 });
		}

		//UI
		{
			Vector2 camSize = pMainCamera->GetComponent<CCamera>()->GetSize();
			CGameObject* pHealthBar = new CGameObject("Health Bar");
			pHealthBar->GetComponent<CTransform>()->SetParent(pMainCamera)->Set_Position({
				10 - camSize.x / 2, 80 - camSize.y / 2
			}, false);
			pHealthBar->AddComponent<CRenderer>()->SetSprite(Texture_Health_Bar, 0)->SetZOrder(-90);

			//Health Bar Value
			{
				CGameObject *pHealthBarValue = new CGameObject("Health Bar Value");
				pHealthBarValue->GetComponent<CTransform>()->SetParent(pHealthBar)->Set_Position({ 0, -16 }, false);
				pHealthBarValue->AddComponent<CRenderer>()->SetSprite(Texture_Health_Bar, 1)->SetZOrder(-100);
				pHealthBarValue->AddComponent<HealthValueController>()->SetTarget(pPlayer);
			}

			//CGameObject* pManaBar = new CGameObject("Mana Bar");
			//pManaBar->GetComponent<CTransform>()->SetParent(pMainCamera)->Set_Position({
			//	30 - camSize.x / 2, 80 - camSize.y / 2
			//}, false);
			//pManaBar->AddComponent<CRenderer>()->SetSprite(Texture_Health_Bar, 2)->SetZOrder(-90);

			////Mana Bar Value
			//{
			//	CGameObject *pManaBarValue = new CGameObject("Mana Bar Value");
			//	pManaBarValue->GetComponent<CTransform>()->SetParent(pManaBar)->Set_Position({ 0, -16 }, false);
			//	pManaBarValue->AddComponent<CRenderer>()->SetSprite(Texture_Health_Bar, 3)->SetZOrder(-100);
			//}
		}

		//Building
		CGameObject* pBuilding = new CGameObject("Building", {4673, 1024-88});
		{
			pBuilding->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 0)->SetZOrder(-5)->GetSprite()->SetAnchor({0,0});
			pBuilding->AddComponent<BuildingController>()->player = pPlayer;
			pPlayer->GetComponent<PlayerController>()->pBuilding = pBuilding;
		}

		//Blast Hornet
		CGameObject* pHornet = new CGameObject("Blast Hornet", Vector2(7890, 1827));
		{
			//Animation
			{
				new CAnimation(Animation_BlastHornet_Flying, Texture_Blast_Hornet, 3, 1);
				anim = new CAnimation(Animation_BlastHornet_StartAttacking, Texture_Blast_Hornet, 3, 13, 100, false);
				anim->Add(Texture_Blast_Hornet, 9, -1, 200);
				new CAnimation(Animation_BlastHornet_Shooting, Texture_Blast_Hornet, 16, 5, 100, false);
				new CAnimation(Animation_BlastHornet_Died, Texture_Blast_Hornet, 21, 1, 2000, false);
			}

			//Properties
			{
				pHornet->AddComponent<CAnimator>()
				       ->AddAnimation(Animation_BlastHornet_Flying)
				       ->AddAnimation(Animation_BlastHornet_StartAttacking)
				       ->AddAnimation(Animation_BlastHornet_Shooting)
				       ->AddAnimation(Animation_BlastHornet_Died)
				       ->AddBool(Bool_IsAttack, false)
				       ->AddBool(Bool_IsShoot, false)
				       ->AddBool(Bool_IsDead, false)

				       ->AddTransition(Animation_BlastHornet_Flying, Animation_BlastHornet_StartAttacking, true, Bool_IsAttack, true)
				       ->AddTransition(Animation_BlastHornet_Flying, Animation_BlastHornet_Shooting, true, Bool_IsShoot, true)
				       ->AddTransition(Animation_BlastHornet_Flying, Animation_BlastHornet_Died, true, Bool_IsDead, true)

				       ->AddTransition(Animation_BlastHornet_StartAttacking, Animation_BlastHornet_Flying, false, Bool_IsAttack, false)
				       ->AddTransition(Animation_BlastHornet_StartAttacking, Animation_BlastHornet_Died, false, Bool_IsDead, true)

				       ->AddTransition(Animation_BlastHornet_Shooting, Animation_BlastHornet_Flying, false, Bool_IsShoot, false)
				       ->AddTransition(Animation_BlastHornet_Shooting, Animation_BlastHornet_Flying, false, Bool_IsShoot, false)
				       ->AddTransition(Animation_BlastHornet_Shooting, Animation_BlastHornet_Died, false, Bool_IsDead, true)
					;
				pHornet->AddComponent<CRenderer>()->SetSprite(Texture_Blast_Hornet, 3);
				pHornet->AddComponent<CRigidbody>()->SetGravityScale(0)->SetLimitedArea(Rect(1807, 7695, 1970, 7940));
				pHornet->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
				pHornet->GetComponent<CBoxCollider>()->SetIsTrigger(true);
				pHornet->AddComponent<BlastHornetController>();
				pHornet->GetComponent<BlastHornetController>()->m_target = pPlayer;
				pHornet->AddComponent<CanAttacked>()->InitDamage(20);
			}

			//Blast Hornet Wing
			{
				new CAnimation(Animation_BlastHornet_Wing, Texture_Blast_Hornet, 0, 3, 25, true);
				Vector2 HornetPos = pHornet->GetComponent<CTransform>()->Get_Position();
				CGameObject* pHornetWing = new CGameObject("Blast Hornet Wing", Vector2(HornetPos.x, HornetPos.y - 30));
				pHornetWing->AddComponent<CTransform>()->SetParent(pHornet);
				pHornetWing->AddComponent<CRenderer>()->SetZOrder(1);
				pHornetWing->AddComponent<CAnimator>()
				           ->AddAnimation(Animation_BlastHornet_Wing);
			}

			//Blast Hornet Child
			new CAnimation(Animation_BlastHornet_Child_Flying, Texture_Blast_Hornet, 37, 6, 10);

			auto childPrefabs = pResourceManager->AddPrefab(Prefab_BlastHornet_Child);
			childPrefabs->AddComponent<CRenderer>();
			childPrefabs->AddComponent<CRigidbody>()->SetGravityScale(0);
			childPrefabs->AddComponent<CAnimator>()
				->AddAnimation(Animation_BlastHornet_Child_Flying);
			childPrefabs->AddComponent<BlastHornetChildController>();
			childPrefabs->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			childPrefabs->GetComponent<CBoxCollider>()->SetSize({ 10,10 });
			childPrefabs->AddComponent<CanAttacked>()->InitDamage(20);
			childPrefabs->SetIsActive(true);
			for (int i = 0; i < 12; i++)
			{
				childPrefabs = CGameObject::Instantiate(Prefab_BlastHornet_Child, nullptr, { 0,0 });
				pHornet->GetComponent<BlastHornetController>()->AddChild(childPrefabs);
			}

			//Blast Hornet Child2
			childPrefabs = pResourceManager->AddPrefab(Prefab_BlastHornet_Child2);
			childPrefabs->AddComponent<CRenderer>();
			childPrefabs->AddComponent<CRigidbody>()->SetGravityScale(0);
			childPrefabs->AddComponent<CAnimator>()
				->AddAnimation(Animation_BlastHornet_Child_Flying);
			childPrefabs->AddComponent<BlastHornetChild2Controller>()->SetParent(pHornet);
			childPrefabs->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			childPrefabs->GetComponent<CBoxCollider>()->SetSize({ 10,10 });
			childPrefabs->AddComponent<CanAttacked>()->InitDamage(20);

			//Blast Hornet bullet
			new CAnimation(Animation_BlastHornet_Bullet_flying, Texture_Blast_Hornet, 43, 2, 50);
			new CAnimation(Animation_BlastHornet_Bullet_targeted, Texture_Blast_Hornet, 45, 2, 50);
			CGameObject* bulletPrefabs = pResourceManager->AddPrefab(Prefab_BlastHornet_Bullet);
			bulletPrefabs->AddComponent<CRigidbody>()->SetGravityScale(0);
			bulletPrefabs->AddComponent<CRenderer>()->SetAlpha(150);
			bulletPrefabs->AddComponent<BlastHornetBulletController>()->SetTarget(pPlayer);
			bulletPrefabs->GetComponent<BlastHornetBulletController>()->SetParent(pHornet);
			bulletPrefabs->AddComponent<CTransform>();
			bulletPrefabs->AddComponent<CBoxCollider>()->SetAutoBoundSize(true);
			bulletPrefabs->GetComponent<CBoxCollider>()->SetIsTrigger(true);
			bulletPrefabs->AddComponent<CAnimator>()
				->AddAnimation(Animation_BlastHornet_Bullet_flying)
				->AddAnimation(Animation_BlastHornet_Bullet_targeted)
				->AddBool(Bool_IsTargeted, false)
				->AddTransition(Animation_BlastHornet_Bullet_flying, Animation_BlastHornet_Bullet_targeted, true, Bool_IsTargeted, true);
		}

		//Launching
		CGameObject* pMachine1 = new CGameObject("Machine_1");
		{
			pMachine1->GetComponent<CTransform>()->Set_Position(Vector2(895, 960));
			pMachine1->AddComponent<CRenderer>()->SetSprite(Texture_Map_Objects, 28)->SetZOrder(-1);
			pMachine1->AddComponent<CAnimator>()
				->AddAnimation(Animation_Machine_1_Idle)
				->AddAnimation(Animation_Machine_1_Run)
				->AddBool(Bool_IsRun, false)
				->AddTransition(Animation_Machine_1_Idle, Animation_Machine_1_Run, true, Bool_IsRun, true)
				->AddTransition(Animation_Machine_1_Run, Animation_Machine_1_Idle, true, Bool_IsRun, false);
			pMachine1->AddComponent<CBoxCollider>()->SetUsedByEffector(false);
			pMachine1->GetComponent<CBoxCollider>()->PlusSize(Vector2(-6, -20));
			pMachine1->GetComponent<CRigidbody>()->SetGravityScale(0)->SetLimitedArea(Rect(Vector2(895, 400), Vector2(0, 560)));
			pMachine1->AddComponent<MachineController>();
			pMachine1->GetComponent<MachineController>()->m_player = pPlayer;
		}

		//NotorBangers
		{
			CGameObject* pNotorBangerEnemy = CGameObject::Instantiate(Prefab_NotorBanger, nullptr, Vector2(200, 875));
			pNotorBangerEnemy->GetComponent<NotorBangerEnemyController>()->SetTarget(pPlayer); 
		}

		//HeadGunners
		{
			CGameObject* pHeadGunnerEnemy = CGameObject::Instantiate(Prefab_HeadGunner, nullptr, Vector2(450, 875));
			pHeadGunnerEnemy->GetComponent<HeadGunnerEnemyController>()->SetTarget(pPlayer);
		}

		//Genjibo
		{
			//Add Animation
			new CAnimation(Animation_Genjibo, Texture_EnemiesAndBosses, 33, 4, 100, true);
			CGameObject* pGenjiBos = new CGameObject("Genjibo", { 2477,980 });
			pGenjiBos->AddComponent<CRenderer>();
			pGenjiBos->AddComponent<CAnimator>()
				->AddAnimation(Animation_Genjibo);
			pGenjiBos->AddComponent<CRigidbody>()->SetGravityScale(0);
			pGenjiBos->SetIsActive(false);
			pPlayer->GetComponent<PlayerController>()->m_GenjiBos = pGenjiBos;


			//Left Missle
			new CAnimation(Animation_Genjibo_Missle_Down, Texture_EnemiesAndBosses, 38, 2, 50);
			const Vector2 GenjiPos = pGenjiBos->GetComponent<CTransform>()->Get_Position();
			CGameObject* pGenjiLeftMissle = new CGameObject("Genjibo Missle", Vector2(GenjiPos.x - 10, GenjiPos.y + 6));
			pGenjiLeftMissle->AddComponent<CTransform>()->SetParent(pGenjiBos);
			pGenjiLeftMissle->AddComponent<CRenderer>()->SetFlipX(true);
			pGenjiLeftMissle->AddComponent<CAnimator>()
				->AddAnimation(Animation_Genjibo_Missle_Down);

			//Bottom led
			CGameObject *pGenjiLight = new CGameObject("Genjibo Light", Vector2(GenjiPos.x, GenjiPos.y + 40));
			pGenjiLight->AddComponent<CTransform>()->SetParent(pGenjiBos);
			pGenjiLight->AddComponent<CRenderer>()->SetSprite(Texture_EnemiesAndBosses, 44);
			pGenjiLight->SetIsActive(false);
			pGenjiBos->AddComponent<GenjiBosController>()->m_light = pGenjiLight;

			//Shurikein
			new CAnimation(Animation_Shurikein_Init, Texture_EnemiesAndBosses, 116, 72, 10, false);
			new CAnimation(Animation_Shurikein_Spinning, Texture_EnemiesAndBosses, 180, 7, 2, true);
			anim = new CAnimation(Animation_Shurikein_WasHit, Texture_EnemiesAndBosses, 180, 1, 50, true);
			anim->Add(Texture_EnemiesAndBosses, 182)
				->Add(Texture_EnemiesAndBosses, 184)
				->Add(Texture_EnemiesAndBosses, 186)
				->Add(Texture_EnemiesAndBosses, 205);

			anim = new CAnimation(Animation_Shurikein_WasHit_3D, Texture_EnemiesAndBosses, 187, 17, 2, true);
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
				->AddAnimation(Animation_Shurikein_Init)
				->AddAnimation(Animation_Shurikein_WasHit)
				->AddAnimation(Animation_Shurikein_WasHit_3D)
				->AddAnimation(Animation_Shurikein_Spinning)
				->AddBool(Bool_IsWasHit, false)
				->AddTransition(Animation_Shurikein_Init, Animation_Shurikein_Spinning)
				->AddTransition(Animation_Shurikein_WasHit, Animation_Shurikein_Spinning)
				->AddTransition(Animation_Shurikein_Spinning, Animation_Shurikein_WasHit, true, Bool_IsWasHit, true)
				;
			pShurikein->AddComponent<ShurikeinController>();
			pShurikein->AddComponent<CRigidbody>()->SetLimitedArea({ {2320, 1040}, {225, 161} })->SetGravityScale(0);
			pShurikein->AddComponent<CBoxCollider>()->SetIsTrigger(true);
			pShurikein->GetComponent<CBoxCollider>()->SetSize(Vector2(47, 47));
			pShurikein->SetIsActive(false);

		}

		//Map Behind
		{
			auto pMapBehind = CGameObject::Instantiate(Prefab_MapBehind_1, pScene->GetMainCamera(), {0, 0});
			pMapBehind->GetComponent<CRenderer>()->SetZOrder(-1);
			pMapBehind->AddComponent<CRenderer>()->SetZOrder(20);
		}

		pMainCamera->GetComponent<CameraController>()->m_player = pPlayer;
		pMainCamera->GetComponent<CameraController>()->SetState(CameraState::Following);

		pGameManager->Run();

	} while (false);

	CGameManager::Destroy();
	CGraphic::Destroy();
	CInput::Destroy();
	
	return 0;
}
