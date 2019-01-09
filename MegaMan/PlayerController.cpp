#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"
#include "CanBeAttacked.h"
#include "CanAttacked.h"
#include "ResourceManager.h"
#include "DashFullEffect.h"
#include "BulletPool.h"
#include "Camera.h"
#include "AudioSource.h"
#include "BuildingController.h"
#include "NotorBangerEnemyController.h"
#include "HeadGunnerEnemyController.h"
#include "HelitController.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"

const Vector2 notorPos[14] = {
	{447 + 26, 853 + 21},
	{701 + 26, 901 + 21},
	{1576 + 26, 645 + 21},
	{1902 + 26, 645 + 21},
	{1576 + 26, 774 + 21},
	{1943 + 26, 774 + 21},
	{1947 + 26, 901 + 21},
	{1576 + 26, 901 + 21},
	{1833 + 26, 1109 + 21},
	{3221 + 26, 923 + 21},
	{3658 + 26, 923 + 21},
	{5955 + 26, 1334 + 21},
	{6039 + 26, 1526 + 21},
	{5987 + 26, 1718 + 21}
};

const Vector2 headPos[8] = {
	{940 + 25, 885 + 30},
	{948 + 25, 628 + 30},
	{795 + 25, 628 + 30},
	{6118 + 25, 1909 + 30},
	{6341 + 25, 1909 + 30},
	{6620 + 25, 1909 + 30},
	{6826 + 25, 1909 + 30},
	{7045 + 25, 1909 + 30}
};

const Vector2 helitPos[8] = {
	{2935 + 25, 850 + 30},
	{3289 + 25, 774 + 30},
	{3366 + 25, 836 + 30},
	{3519 + 25, 836 + 30},
	{3809 + 25, 836 + 30},
};

PlayerController::PlayerController(const PlayerController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
	pGenjibo = PC.pGenjibo;
	m_Power = PC.m_Power;
	m_canMove = PC.m_canMove;
	m_onMachine = PC.m_onMachine;
}

PlayerController::PlayerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

void PlayerController::Start()
{
	m_DashEffect = CGameObject::Instantiate(Prefab_Effect_Dash, m_pGameObject);
	m_DashEffect->SetIsActive(false);

	anim = m_pGameObject->GetComponent<CAnimator>();
	transform = m_pGameObject->GetComponent<CTransform>();
	rigidBody = m_pGameObject->GetComponent<CRigidbody>();
	renderer = m_pGameObject->GetComponent<CRenderer>();
	input = CInput::GetInstance();
	mainCamera = m_pGameObject->GetScene()->GetMainCamera()->GetComponent<CameraController>();

	m_pNotorPrefab = CResourceManager::GetInstance()->GetPrefab(Prefab_NotorBanger);
	m_pHeadPrefab = CResourceManager::GetInstance()->GetPrefab(Prefab_HeadGunner);
	m_pHelitPrefab = CResourceManager::GetInstance()->GetPrefab(Prefab_Helit);

	for (int i = 0; i < 14; ++i)
	{
		m_pNotors[i] = CGameObject::Instantiate(m_pNotorPrefab, nullptr, notorPos[i]);
		m_pNotors[i]->GetComponent<NotorBangerEnemyController>()->SetTarget(m_pGameObject);
	}
	for (int i = 0; i < 8; ++i)
	{
		m_pHeads[i] = CGameObject::Instantiate(m_pHeadPrefab, nullptr, headPos[i]);
		m_pHeads[i]->GetComponent<HeadGunnerEnemyController>()->SetTarget(m_pGameObject);
	}
	for (int i = 0; i < 5; ++i)
	{
		m_pHelits[i] = CGameObject::Instantiate(m_pHelitPrefab, nullptr, helitPos[i]);
		m_pHelits[i]->GetComponent<HelitController>()->SetTarget(m_pGameObject);
	}
}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	auto anim = m_pGameObject->GetComponent<CAnimator>();
	if(strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("Wall").c_str()))
	{
		anim->SetBool(Bool_IsClinging, true);
		anim->SetBool(Bool_IsJump, false);
	}

	if (strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("Machine").c_str()))
	{
		m_onMachine = true;
	}
	if (collision->GetOtherCollider()->GetComponent<CanAttacked>())
	{
		m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Megaman_wasHit);
	}
	//m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsJump, false);
}

void PlayerController::OnTriggerEnter(CCollision* collision)
{
	if (collision->GetOtherCollider()->GetComponent<CanAttacked>())
	{
		m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Megaman_wasHit);
		m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsWasHit, true);
		m_canMove = false;
	}

	if (strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("DeadHole").c_str()))
	{
		m_pGameObject->GetComponent<CanBeAttacked>()->ForceDie();
	}
}

void PlayerController::Update(const DWORD &dt)
{
	CheckEnemies();

	if(const auto canBeAttacked = m_pGameObject->GetComponent<CanBeAttacked>())
	{
		if(canBeAttacked->GetCurrentHealth() <= 0)
		{
			m_isAlive = false;
		}
	}

	if (m_isAlive) {
		CheckFightBoss();
		Action(dt);
		Move();
	}
	else
	{
		if (m_DieEffect) {
			m_DieEffect->SetIsActive(true);
			m_waitDie -= dt;
			if(m_waitDie<0)
			{
				PostQuitMessage(0);
			}
		}
	}
}

void PlayerController::Action(const DWORD &dt)
{
	if (!m_canAction) return;
	const Vector2 velocity = rigidBody->GetVelocity();
	const bool isLeft = renderer->GetFlipX();
	if (anim->GetBool(Bool_IsShoot))
		anim->SetBool(Bool_IsShoot, false);
	if (anim->GetBool(Bool_IsWasHit) && anim->GetCurrentAnimation()->IsLastFrame())
	{
		anim->SetBool(Bool_IsWasHit, false);
		m_canMove = true;
	}

	if (velocity.y > 0)
	{
		anim->SetBool(Bool_IsFall, true);
		anim->SetBool(Bool_IsLandFall, false);
		anim->SetBool(Bool_IsSkyWalk, false);
	}
	else if (velocity.y == 0) {
		if (anim->GetBool(Bool_IsFall))
		{
			anim->SetBool(Bool_IsLandFall, true);
			anim->SetBool(Bool_IsClinging, false);
			anim->SetBool(Bool_IsFall, false);
			anim->SetBool(Bool_IsJump, false);
			m_skyWalked = false;
		}


	}
	else {
		anim->SetBool(Bool_IsFall, false);
		anim->SetBool(Bool_IsLandFall, false);
	}

	if (anim->GetBool(Bool_IsSkyWalk) && anim->GetCurrentAnimation()->IsLastFrame())
	{
		anim->SetBool(Bool_IsSkyWalk, false);
	}

	if (anim->GetBool(Bool_IsDash) && anim->GetCurrentAnimation()->IsLastFrame())
	{
		if (!anim->GetBool(Bool_IsRun))
		{
			rigidBody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
		else
		{
			rigidBody->SetVelocity(Vector2(isLeft ? -m_speed : m_speed, MAX_VELOCITY));
		}

		m_DashFullEffectEffect->GetComponent<DashFullEffect>()->SetIsDashing(false);
		anim->SetBool(Bool_IsDash, false);
	}

	if (anim->GetBool(Bool_IsDash) && !anim->GetCurrentAnimation()->IsLastFrame())
	{
		rigidBody->SetVelocity(Vector2(isLeft ? -0.3 : 0.3, MAX_VELOCITY));
		m_DashFullEffectEffect->GetComponent<DashFullEffect>()->SetIsDashing(true)->SetIsLeft(isLeft);
	}
	if (input->KeyDown(Key_Shoot)) {
		// anim->SetBool(Bool_IsShoot, true);
		// Shoot();
	}
	if (input->KeyHold(Key_Shoot)) {
		m_pressTime += dt;
		if (m_pressTime > CHARGELV1_TIME)
			if (m_pressTime < CHARGELV2_TIME)
			{
				m_Power->SetIsActive(true);
			}
			else
			{
				m_Power->GetComponent<CAnimator>()->SetBool(Bool_IsChargeFull, true);
			}
	}
	if (input->KeyUp(Key_Shoot)) {
		m_Power->GetComponent<CAnimator>()->SetBool(Bool_IsChargeFull, false);
		m_Power->SetIsActive(false);
		anim->SetBool(Bool_IsShoot, true);
		Shoot();
		m_pressTime = 0;
	}

	if (input->KeyDown(Key_Surf)) {
		if (!anim->GetBool(Bool_IsDash)) {
			m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Megaman_Dash);
			anim->SetBool(Bool_IsDash, true);
			Dash(isLeft);
		}
	}

	if (anim->GetBool(Bool_IsLandFall) || anim->GetBool(Bool_IsJump))
	{
		anim->SetBool(Bool_IsClinging, false);
	}

	/*if (input->KeyDown(DIK_F))
	{
		if (!anim->GetBool(Bool_IsCut))
		{
			anim->SetBool(Bool_IsCut, true);
		}
	}
	if (input->KeyUp(DIK_F))
	{
		if (anim->GetBool(Bool_IsCut))
		{
			anim->SetBool(Bool_IsCut, false);
		}
	}*/

	if (input->KeyDown(DIK_E)) {
		if (m_Power)
			m_Power->SetIsActive(true);
	}
	if (input->KeyUp(DIK_E)) {
		if (m_Power)
			m_Power->SetIsActive(false);
	}
}

void PlayerController::Move()
{
	if (!m_canMove)
	{
		rigidBody->SetVelocity({ 0,0 });
		return;
	}
	const bool isLeft = renderer->GetFlipX();

	if (input->KeyDown(Key_Jump)) {
		if (!anim->GetBool(Bool_IsJump) && !anim->GetBool(Bool_IsClinging)) {
			anim->SetBool(Bool_IsJump, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
			m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Megaman_Jump);
		}
		else
		{
			if (anim->GetBool(Bool_IsClinging))
			{

				rigidBody->SetVelocity(Vector2(Jump_Wall_Velocity*(isLeft ? 1 : -1), -Jump_Wall_Velocity));
				anim->SetBool(Bool_IsRun, false);
				anim->SetBool(Bool_IsJump, true);
				m_DashEffect->GetComponent<CTransform>()->Set_Position(m_pGameObject->GetComponent<CTransform>()->Get_Position() + Vector2(0, 17), false);
				m_DashEffect->SetIsActive(true);
				m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_Megaman_Jump);
			}
			else
			{
				if (!m_skyWalked) {
					anim->SetBool(Bool_IsSkyWalk, true);
					rigidBody->AddVelocity(Vector2(0, -Jump_Sky_Velocity));
					m_skyWalked = true;
				}
			}

		}

		if (anim->GetBool(Bool_IsFall))
		{
			anim->SetBool(Bool_IsSkyWalk, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
		}

		// if (anim->GetBool(Bool_IsClinging)) {
		// 	rigidBody->AddVelocity(Vector2(Jump_Velocity * (isLeft ? 1 : -1), 0));
		// 	anim->SetBool(Bool_IsRun, false);
		// }
	}

	// if (anim->GetBool(Bool_IsClinging) && anim->GetBool(Bool_IsJump))
	// {
	// 	rigidBody->SetVelocity(Vector2(isLeft ? Jump_Velocity / 4 : -Jump_Velocity / 4, -Jump_Velocity / 2));
	// 	anim->SetBool(Bool_IsClinging, false);
	// }

	/*if (input->KeyDown(Key_MoveLeft)) {
		renderer->SetFlipX(true);
		anim->SetBool(Bool_IsRun, true);
		rigidBody->AddVelocity(Vector2(-m_speed, 0));
	}*/

	if (input->KeyHold(Key_MoveRight)) {
		renderer->SetFlipX(false);
		if (!anim->GetBool(Bool_IsRun))
		{
			rigidBody->AddVelocity(Vector2(m_speed, 0));
			anim->SetBool(Bool_IsRun, true);
		}
		return;
	}
	else {
		if (anim->GetBool(Bool_IsRun)) {
			anim->SetBool(Bool_IsRun, false);
			rigidBody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

	if (input->KeyHold(Key_MoveLeft)) {
		renderer->SetFlipX(true);
		if (!anim->GetBool(Bool_IsRun))
		{
			rigidBody->AddVelocity(Vector2(-m_speed, 0));
			anim->SetBool(Bool_IsRun, true);
		}
		return;
	}
	else {
		if (anim->GetBool(Bool_IsRun)) {
			anim->SetBool(Bool_IsRun, false);
			rigidBody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

}

void PlayerController::Dash(bool isLeft) const
{
	Vector2 pos = { 0,17 };
	pos.x += isLeft ? 15 : -15;
	m_DashEffect->SetIsActive(true);
	m_DashEffect->GetComponent<CTransform>()->Set_Position(pos, false);
	m_DashEffect->GetComponent<CRenderer>()->SetFlipX(!isLeft);

}

void PlayerController::Shoot() const
{
	const bool isLeft = m_pGameObject->GetComponent<CRenderer>()->GetFlipX();
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	auto animator = m_pGameObject->GetComponent<CAnimator>();
	pos.x += (isLeft ? -1 : 1) * 15;
	if (animator->GetBool(Bool_IsShoot))
	{
		if (m_pressTime < CHARGELV1_TIME)
		{
			m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_MegaMan_Shoot);
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_BusterShot, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });

		}
		else if (m_pressTime < CHARGELV2_TIME)
		{
			m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_MegaMan_Power_Shoot);
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_ChargeShotLV1, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
			pBullet->GetComponent<CRenderer>()->SetFlipX(isLeft);
		}
		else
		{
			m_pGameObject->GetComponent<CAudioSource>()->Play(Audio_MegaMan_Power_Shoot);
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_ChargeShotLV2, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
			pBullet->GetComponent<CRenderer>()->SetFlipX(isLeft);
		}
		// animator->SetBool(Bool_IsShoot, false);
	}
}

void PlayerController::CheckFightBoss()
{		
	if(transform->Get_Position().x > 7696)
	{
		if(pBlastHornet)
		{
			if(pBlastHornet->GetComponent<CanBeAttacked>()->IsAlive())
			{
				pBlastHornet->SetIsActive(true);
			}
			else
			{
				pBlastHornet = nullptr;
			}
		}
	}
	else if (transform->Get_Position().x > 4673 && transform->Get_Position().x < 4673 + 256) {
		if(pBuilding)
		{
			if (!pBuilding->GetComponent<BuildingController>()->CheckTurnedOn()) //Building hasn't started
			{
				pBuilding->SetIsActive(true);
				pBuilding->GetComponent<BuildingController>()->TurnOn();
			}
			else if (!pBuilding->GetIsActive()) //Building ended
			{
				mainCamera->SetBlockChangeBound(false); //Unlock Camera
				pBuilding = nullptr;
			}
			else //Building started but hasn't ended
			{
				mainCamera->SetBlockChangeBound(true); //Lock Camera can't move
			}
		}
	}
	else if (transform->Get_Position().x > 2320 && transform->Get_Position().x < 2320 + 256) {
		if(pGenjibo)
			if (pShurikein->GetComponent<CanBeAttacked>()->IsAlive())
			{
				pGenjibo->SetIsActive(true);
			}
			else
			{
				pGenjibo = nullptr;
			}
	}
}

void PlayerController::CheckEnemies()
{
	const auto pos = transform->Get_Position();
	auto bound = Bound(pos - Vector2(178,178), { 356, 356 });
	for (int i = 0; i < 14; ++i)
	{
		if (!m_pNotors[i]) continue;
		if(bound.isInside(m_pNotors[i]->GetPosition()))
		{
			if (m_pNotors[i]->GetComponent<CanBeAttacked>()->IsAlive()) 
				//*m_pNotors[i] = *m_pNotorPrefab;
				m_pNotors[i]->SetIsActive(true);
		}
		else
			m_pNotors[i]->SetIsActive(false);
	}
	for (int i = 0; i < 8; ++i)
	{
		if (!m_pHeads[i]) continue;
		if (bound.isInside(m_pHeads[i]->GetPosition()))
		{
			if (m_pHeads[i]->GetComponent<CanBeAttacked>()->IsAlive())
				//*m_pNotors[i] = *m_pNotorPrefab;
				m_pHeads[i]->SetIsActive(true);
		}
		else
			m_pHeads[i]->SetIsActive(false);
	}
	for (int i = 0; i < 5; ++i)
	{
		if (!m_pHelits[i]) continue;
		if (bound.isInside(m_pHelits[i]->GetPosition()))
		{
			if (m_pHelits[i]->GetComponent<CanBeAttacked>()->IsAlive())
				//*m_pNotors[i] = *m_pNotorPrefab;
				m_pHelits[i]->SetIsActive(true);
		}
		else
			m_pHelits[i]->SetIsActive(false);
	}
}
