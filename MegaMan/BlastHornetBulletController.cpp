#include "BlastHornetBulletController.h"
#include "BlastHornetController.h"

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

BlastHornetBulletController::~BlastHornetBulletController()
{
}

void BlastHornetBulletController::OnTriggerEnter(Framework::CCollision* collision)
{
	std::string collisionName = collision->GetOtherCollider()->GetName();
	if (strstr(collisionName.c_str(), "Player"))
	{
		m_pGameObject->GetComponent<CAnimator>()->SetBool("isTargeted", true);
		m_parent->GetComponent<BlastHornetController>()->m_isTargeted = true;
	}
}


void BlastHornetBulletController::Update(DWORD dt)
{
	Vector2 targetPos = m_target->GetComponent<CTransform>()->Get_Position();
	auto rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	auto transform = m_pGameObject->GetComponent<CTransform>();
	auto animator = m_pGameObject->GetComponent<CAnimator>();

	m_flyTime -= dt;
	if(animator->GetBool("isTargeted"))
	{
		transform->Set_Position(targetPos);
		m_flyTime = 5000;
		m_targetTime -= dt;
	}
	else
	{
		Vector2 velocity;
		Vector2 distance = targetPos - transform->Get_Position();
		if (distance.x < 0) velocity.x = -0.05; else if (distance.x > 0) velocity.x = 0.05; else if (distance.x == 0) velocity.x = 0;
		if (distance.y < 0) velocity.y = -0.05; else if (distance.y > 0) velocity.y = 0.05; else if (distance.y == 0) velocity.y = 0;
		rigidbody->SetVelocity(velocity);
	}
	if (m_flyTime <= 0 || m_targetTime <= 0)
	{
		m_parent->GetComponent<BlastHornetController>()->m_isTargeted = false;
		SAFE_DELETE(m_pGameObject);
	}
}

void BlastHornetBulletController::Render()
{
}
