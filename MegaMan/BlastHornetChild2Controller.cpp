#include "BlastHornetChild2Controller.h"
#include "Animator.h"
#include "Renderer.h"
#include "BlastHornetController.h"

BlastHornetChild2Controller::BlastHornetChild2Controller(const BlastHornetChild2Controller& PC) : CMonoBehavior(PC)
{
	m_target = PC.m_target;
	m_parent = PC.m_parent;
}

BlastHornetChild2Controller* BlastHornetChild2Controller::Clone() 
{
	return new BlastHornetChild2Controller(*this);
}

BlastHornetChild2Controller::BlastHornetChild2Controller(CGameObject* gameObject) :CMonoBehavior( gameObject)
{
}

BlastHornetChild2Controller::~BlastHornetChild2Controller()
{
}

void BlastHornetChild2Controller::OnTriggerEnter(CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (!strstr(collisionName.c_str(), "BlastHornet") && !strstr(collisionName.c_str(), "Blast Hornet"))
	{
		Explosive();
	}
}

void BlastHornetChild2Controller::Update(DWORD dt)
{
	Vector2 targetPos = m_target->GetComponent<CTransform>()->Get_Position();
	Vector2 parentPos = m_parent->GetComponent<CTransform>()->Get_Position();
	auto transform = m_pGameObject->GetComponent<CTransform>();
	auto animator = m_pGameObject->GetComponent<CAnimator>();
	auto rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	auto renderer = m_pGameObject->GetComponent<CRenderer>();
	Vector2 myPos = transform->Get_Position();
	Vector2 distance;
	Vector2 velocity = rigidbody->GetVelocity();
	if (!animator->GetBool("wasHit"))
	{
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
	}
	else velocity = Vector2({ 0,0 });
	rigidbody->SetVelocity(velocity);
	//delete child
	if (animator->GetBool("wasHit") && animator->GetCurrentAnimation()->IsLastFrame())
	{
		SAFE_DELETE(m_pGameObject);
	}
}

void BlastHornetChild2Controller::Render()
{
}

void BlastHornetChild2Controller::Explosive()
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool("wasHit", true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 })->SetGravityScale(0);

}