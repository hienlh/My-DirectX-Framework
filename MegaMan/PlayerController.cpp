#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"
#include "CanBeAttacked.h"
#include "ResourceManager.h"
#include "DashFullEffect.h"
#include "BulletPool.h"
#include "Camera.h"
#include "BuildingController.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "Macros.h"
#include "HealItemController.h"

PlayerController::PlayerController(const PlayerController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
	m_GenjiBos = PC.m_GenjiBos;
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
}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	auto anim = m_pGameObject->GetComponent<CAnimator>();
	auto renderer = m_pGameObject->GetComponent<CRenderer>();
	auto transform = m_pGameObject->GetComponent<CTransform>();
	std::string name = collision->GetOtherCollider()->GetName();
	// CDebug::Log("Collision:" + name);
	if(strstr(name.c_str(), "Heath_Item"))
	{
		m_pGameObject->GetComponent<CanBeAttacked>()->Heal(collision->GetOtherCollider()->GetComponent<HealItemController>()->GetHealValue());
		collision->GetOtherCollider()->GetComponent<HealItemController>()->isCollision = true;
	}
	if(strstr(name.c_str(), std::string("Wall").c_str()))
	{
		renderer->SetFlipX(!renderer->GetFlipX());
		anim->SetBool(Bool_IsClinging, true);
		anim->SetBool(Bool_IsJump, false);
	}
	if(strstr(name.c_str(), std::string("Wall").c_str()))
	{
		renderer->SetFlipX(!renderer->GetFlipX());
		anim->SetBool(Bool_IsClinging, true);
		anim->SetBool(Bool_IsJump, false);
	}
	if(strstr(name.c_str(),"Ground"))
	{
		anim->SetBool(Bool_IsLandFall, true);
		anim->SetBool(Bool_IsClinging, false);
		anim->SetBool(Bool_IsFall, false);
		anim->SetBool(Bool_IsJump, false);
		m_onScrollWheelLeft = false;
		m_onScrollWheelRight = false;
	}

	if (strstr(name.c_str(), std::string("Machine").c_str()))
	{
		m_onMachine = true;
	}
	if(strstr(name.c_str(),"ScrollingWell_1") || strstr(name.c_str(), "ScrollingWell_3"))
	{
		m_onScrollWheelLeft = true;
	}else if(strstr(name.c_str(),"ScrollingWell_2"))
	{
		m_onScrollWheelRight = true;
	}

	//m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsJump, false);
}

void PlayerController::OnTriggerEnter(CCollision* collision)
{
	// std::string name = collision->GetOtherCollider()->GetName();
	// if(!strstr(name.c_str(),Prefab_BlastHornet_Bullet))
	// {
		// if (strstr(name.c_str(), "Bullet") || strstr(name.c_str(), "Blast Hornet") || strstr(name.c_str(), "BlastHornet"))
		if (collision->GetOtherCollider()->GetComponent<CanAttacked>())
		{
			m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsWasHit, true);
			m_canMove = false;
		}
	// }
}

void PlayerController::Update(const DWORD &dt)
{
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
		if(m_onScrollWheelLeft)
		{
			m_pGameObject->GetComponent<CTransform>()->Translate(Vector2( -0.05*dt,0 ));
		} else if(m_onScrollWheelRight)
		{
			m_pGameObject->GetComponent<CTransform>()->Translate(Vector2(0.05*dt, 0));
		}
	}
	else
	{
		if (m_DieEffect)
			m_DieEffect->SetIsActive(true);
	}
}

void PlayerController::Action(DWORD dt)
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
	if (input->KeyDown(DIK_SPACE)) {
		// anim->SetBool(Bool_IsShoot, true);
		// Shoot();
	}
	if (input->KeyHold(DIK_SPACE)) {
		m_pressTime += dt;
		if (m_pressTime > CHARGELV1_TIME) 
			if(m_pressTime < CHARGELV2_TIME)
			{
				m_Power->SetIsActive(true);
			}
			else
			{
				m_Power->GetComponent<CAnimator>()->SetBool(Bool_IsChargeFull, true);
			}
	}
	if (input->KeyUp(DIK_SPACE)) {
		m_Power->GetComponent<CAnimator>()->SetBool(Bool_IsChargeFull, false);
		m_Power->SetIsActive(false);
		anim->SetBool(Bool_IsShoot, true);
		Shoot();
		m_pressTime = 0;
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool(Bool_IsDash)) {
			anim->SetBool(Bool_IsDash, true);
			Dash(isLeft);
		}
	}

	if (anim->GetBool(Bool_IsLandFall) || anim->GetBool(Bool_IsJump))
	{
		anim->SetBool(Bool_IsClinging, false);
	}

	if (input->KeyDown(DIK_F))
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
	}

	if (input->KeyDown(DIK_E)) {
		if (m_Power)
			m_Power->SetIsActive(true);
	}
	if (input->KeyUp(DIK_E)) {
		if (m_Power)
			m_Power->SetIsActive(false);
	}

	if (transform->Get_Position().x > 2320)
	{
		if (m_GenjiBos && !m_GenjiBos->GetIsActive())
			m_GenjiBos->SetIsActive(true);
	}
}

void PlayerController::Move() const
{
	if (!m_canMove)
	{
		rigidBody->SetVelocity({ 0,0 });
		return;
	}
	const bool isLeft = renderer->GetFlipX();

	if (input->KeyDown(DIK_UPARROW)) {
		if (!anim->GetBool(Bool_IsJump) && !anim->GetBool(Bool_IsClinging)) {
			anim->SetBool(Bool_IsJump, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
		}
		else
		{
			if(anim->GetBool(Bool_IsClinging))
			{

				rigidBody->SetVelocity(Vector2(Jump_Velocity*(isLeft ? 1 : -1), -Jump_Velocity));
				anim->SetBool(Bool_IsRun, false);
				anim->SetBool(Bool_IsJump, true);
				m_DashEffect->GetComponent<CTransform>()->Set_Position(m_pGameObject->GetComponent<CTransform>()->Get_Position() + Vector2(0,17), false);
				m_DashEffect->SetIsActive(true);
			}
			else
			{
				anim->SetBool(Bool_IsSkyWalk, true);
				rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
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

	/*if (input->KeyDown(DIK_LEFTARROW)) {
		renderer->SetFlipX(true);
		anim->SetBool(Bool_IsRun, true);
		rigidBody->AddVelocity(Vector2(-m_speed, 0));
	}*/

	if (input->KeyHold(DIK_RIGHTARROW)) {
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
	
	if (input->KeyHold(DIK_LEFTARROW)) {
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
	if(animator->GetBool(Bool_IsShoot))
	{
		if (m_pressTime < CHARGELV1_TIME)
		{
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_BusterShot, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
			
		}
		else if(m_pressTime < CHARGELV2_TIME)
		{
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_ChargeShotLV1, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
			pBullet->GetComponent<CRenderer>()->SetFlipX(isLeft);
		}
		else
		{
			auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_ChargeShotLV2, pos); //CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
			pBullet->GetComponent<CRigidbody>()->SetVelocity({ static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
			pBullet->GetComponent<CRenderer>()->SetFlipX(isLeft);
		}
		// animator->SetBool(Bool_IsShoot, false);
	}
	
	
}

void PlayerController::CheckFightBoss()
{
	if(m_isFightingBoss)
	{
		if (!mainCamera->GetBlockChangeBound())
			mainCamera->SetBlockChangeBound(true);

	}
	else
	{
		/*if (transform->Get_Position().x > 2816 + 1857) {
			m_isFightingBoss = true;
			pBuilding->GetComponent<BuildingController>()->TurnOn();
		}
		if(mainCamera->GetBlockChangeBound())
			mainCamera->SetBlockChangeBound(false);*/
	}
}

void PlayerController::PassBuilding()
{
	m_isFightingBoss = false;
	mainCamera->SetBlockChangeBound(false);
}
