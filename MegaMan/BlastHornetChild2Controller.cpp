#include "BlastHornetChild2Controller.h"
#include "Animator.h"
#include "Renderer.h"
#include "BlastHornetController.h"
#include "Macros.h"
#include "EffectPool.h"

BlastHornetChild2Controller::BlastHornetChild2Controller(const BlastHornetChild2Controller& PC) : CMonoBehavior(PC)
{
	m_target = PC.m_target;
	m_parent = PC.m_parent;
}

BlastHornetChild2Controller* BlastHornetChild2Controller::Clone()
{
	return new BlastHornetChild2Controller(*this);
}

BlastHornetChild2Controller::BlastHornetChild2Controller(CGameObject* gameObject) :CMonoBehavior(gameObject)
{
}

void BlastHornetChild2Controller::Start()
{
	anim = m_pGameObject->GetComponent <CAnimator>();
	transform = m_pGameObject->GetComponent <CTransform>();
	rigid = m_pGameObject->GetComponent <CRigidbody>();
	renderer = m_pGameObject->GetComponent <CRenderer>();
}

void BlastHornetChild2Controller::OnTriggerEnter(CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (!strstr(collisionName.c_str(), "BlastHornet") && !strstr(collisionName.c_str(), "Blast Hornet"))
	{
		Explosive();
	}
}

void BlastHornetChild2Controller::Update(const DWORD& dt)
{
	lifeTime -= dt;
	if (lifeTime <= 0)
	{
		Explosive();
	}
	else
	{
		const Vector2 targetPos = m_target->GetPosition();
		const Vector2 parentPos = m_parent->GetPosition();

		const Vector2 myPos = transform->Get_Position();

		Vector2 distance;
		Vector2 velocity;
		if (m_parent->GetComponent<BlastHornetController>()->m_isTargeted) {
			distance = targetPos - myPos;
			if (distance.x < 0) velocity.x = -0.05; else if (distance.x > 0) velocity.x = 0.05; else velocity.x = 0;
			if (distance.y < 0) velocity.y = -0.05; else if (distance.y > 0) velocity.y = 0.05; else velocity.y = 0;
			if (distance.x + 5 < 0) renderer->SetFlipX(false); else if (distance.x - 5 > 0) renderer->SetFlipX(true);
		}
		else
		{
			distance = parentPos - myPos;
			if (distance.x < -25) velocity.x = -0.05; else if (distance.x > 25) velocity.x = 0.05; else velocity.x = 0;
			if (distance.y < -31) velocity.y = -0.05; else if (distance.y > 31) velocity.y = 0.05; else velocity.y = 0;
			if (distance.x + 5 < 0) renderer->SetFlipX(false); else if (distance.x - 5 > 0) renderer->SetFlipX(true);
		}
		rigid->SetVelocity(velocity);
	}
}

void BlastHornetChild2Controller::Explosive() const
{
	EffectPool::GetInstance()->CreateEffect(Prefab_Effect_Explode, transform->Get_Position());
	m_pGameObject->SetIsActive(false);
}
