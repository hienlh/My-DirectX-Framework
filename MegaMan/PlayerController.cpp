#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"
#include "GameManager.h"

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
	anim = m_pGameObject->GetComponent<CAnimator>();
	transform = m_pGameObject->GetComponent<CTransform>();
	rigidBody = m_pGameObject->GetComponent<CRigidbody>();
	renderer = m_pGameObject->GetComponent<CRenderer>();
	input = CInput::GetInstance();
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

	//m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsJump, false);
}

void PlayerController::OnTriggerEnter(CCollision* collision)
{
	if (!strstr(collision->GetOtherCollider()->GetName().c_str(), "BlastHornetBullet"))
	{
		if (strstr(collision->GetOtherCollider()->GetName().c_str(), "Bullet") || strstr(
			collision->GetOtherCollider()->GetName().c_str(), "BlastHornet") || strstr(
			collision->GetOtherCollider()->GetName().c_str(), "Blast Hornet"))
		{
			m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsWasHit, true);
			m_canMove = false;
		}
		
	}
}

void PlayerController::Update(DWORD dt)
{
	Action();
	Move();
	if (m_pGameObject->GetComponent<CAnimator>()->GetBool(Bool_IsWasHit)) m_pGameObject->GetComponent<CRigidbody>()->SetGravityScale(0);
	else m_pGameObject->GetComponent<CRigidbody>()->SetGravityScale(1);
}

void PlayerController::Action()
{
	if (!m_canAction) return;
	const Vector2 velocity = rigidBody->GetVelocity();
	const bool isLeft = renderer->GetFlipX();

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
		if (anim->GetBool(Bool_IsFall)) anim->SetBool(Bool_IsLandFall, true);
		anim->SetBool(Bool_IsClinging, false);
		anim->SetBool(Bool_IsFall, false);
		anim->SetBool(Bool_IsJump, false);
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
			rigidBody->SetVelocity(Vector2(isLeft ? -.2 : .2, MAX_VELOCITY));
		}
		anim->SetBool(Bool_IsDash, false);
	}

	if (anim->GetBool(Bool_IsDash) && !anim->GetCurrentAnimation()->IsLastFrame())
	{
		rigidBody->SetVelocity(Vector2(isLeft ? -0.2 : 0.2, MAX_VELOCITY));
	}

	if (input->KeyDown(DIK_SPACE)) {
		anim->SetBool(Bool_IsShoot, true);
		Shoot();
	}
	if (input->KeyUp(DIK_SPACE)) {
		anim->SetBool(Bool_IsShoot, false);
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool(Bool_IsDash)) {
			anim->SetBool(Bool_IsDash, true);
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
		if (!anim->GetBool(Bool_IsJump)) {
			anim->SetBool(Bool_IsJump, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
		}
		else
		{
			anim->SetBool(Bool_IsSkyWalk, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
		}

		if (anim->GetBool(Bool_IsFall))
		{
			anim->SetBool(Bool_IsSkyWalk, true);
			rigidBody->AddVelocity(Vector2(0, -Jump_Velocity));
		}

		if (anim->GetBool(Bool_IsClinging)) {
			rigidBody->AddVelocity(Vector2(Jump_Velocity * (isLeft ? 1 : -1), 0));
			anim->SetBool(Bool_IsRun, false);
		}
	}

	if (anim->GetBool(Bool_IsClinging) && anim->GetBool(Bool_IsJump))
	{
		rigidBody->SetVelocity(Vector2(isLeft ? Jump_Velocity / 4 : -Jump_Velocity / 4, -Jump_Velocity / 2));
		anim->SetBool(Bool_IsClinging, false);
	}

	//TODO fix move = keyhole
	/*if (input->KeyDown(DIK_LEFTARROW)) {
		renderer->SetFlipX(true);
		anim->SetBool(Bool_IsRun, true);
		rigidBody->AddVelocity(Vector2(-m_speed, 0));
	}*/

	if (input->KeyHold(DIK_RIGHTARROW)) {
		renderer->SetFlipX(false);
		if (!anim->GetBool(Bool_IsRun)) {
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
		if (!anim->GetBool(Bool_IsRun)) {
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

void PlayerController::Shoot() const
{
	const bool isLeft = m_pGameObject->GetComponent<CRenderer>()->GetFlipX();
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	pos.x += (isLeft ? -1 : 1) * 15;
	auto pBullet = CGameObject::Instantiate(Prefab_BusterShot, nullptr, pos);
	pBullet->GetComponent<CRigidbody>()->SetVelocity({static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
}
