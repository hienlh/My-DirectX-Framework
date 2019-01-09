#include "BoxEndController2.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"

void BoxEndController2::Update(const DWORD& dt)
{
	if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(
			Prefab_Effect_Explode, m_pGameObject->GetComponent<Framework::CBoxCollider>()->GetBoundGlobal(), 2);
	}
}

void BoxEndController2::OnTriggerEnter(Framework::CCollision* collision)
{
	if (strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("DeadHole").c_str()))
	{
		m_pGameObject->GetComponent<CanBeAttacked>()->ForceDie();
	}
	if (strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("Player").c_str())
		|| strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("Ground").c_str()))
	{
		m_pGameObject->GetComponent<CanBeAttacked>()->ForceDie();
	}
}

void BoxEndController2::OnCollisionEnter(Framework::CCollision* collision)
{
}
