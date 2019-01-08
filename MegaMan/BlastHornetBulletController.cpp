#include "BlastHornetBulletController.h"
#include "BlastHornetController.h"
#include "Macros.h"

BlastHornetBulletController::BlastHornetBulletController(const BlastHornetBulletController& PC) : CMonoBehavior(PC)
{
	m_target = PC.m_target;
	m_flyTime = PC.m_flyTime;
	m_targetTime = PC.m_targetTime;
	m_parent = PC.m_parent;
}

BlastHornetBulletController* BlastHornetBulletController::Clone()
{
	return new BlastHornetBulletController(*this);
}

BlastHornetBulletController::BlastHornetBulletController(CGameObject * gameObject) : CMonoBehavior(gameObject)
{
}

void BlastHornetBulletController::Start()
{
	rigid = m_pGameObject->GetComponent<CRigidbody>();
	transform = m_pGameObject->GetComponent<CTransform>();
	anim = m_pGameObject->GetComponent<CAnimator>();
}

void BlastHornetBulletController::OnTriggerEnter(Framework::CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (strstr(collisionName.c_str(), "Player"))
	{
		anim->SetBool(Bool_IsTargeted, true);
		m_parent->GetComponent<BlastHornetController>()->m_isTargeted = true;
	}
}


void BlastHornetBulletController::Update(const DWORD& dt)
{
	const Vector2 targetPos = m_target->GetPosition();

	m_flyTime -= dt;
	if (anim->GetBool(Bool_IsTargeted))
	{
		transform->Set_Position(targetPos);
		m_flyTime = 5000;
		m_targetTime -= dt;
	}
	else
	{
		Vector2 velocity;
		const Vector2 distance = targetPos - transform->Get_Position();
		if (distance.x < 0) velocity.x = -0.05; else if (distance.x > 0) velocity.x = 0.05; else if (distance.x == 0) velocity.x = 0;
		if (distance.y < 0) velocity.y = -0.05; else if (distance.y > 0) velocity.y = 0.05; else if (distance.y == 0) velocity.y = 0;
		rigid->SetVelocity(velocity);
	}

	if (m_flyTime <= 0 || m_targetTime <= 0)
	{
		m_parent->GetComponent<BlastHornetController>()->m_isTargeted = false;
		m_pGameObject->SetIsActive(false);
	}
}
