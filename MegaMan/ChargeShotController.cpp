#include "ChargeShotController.h"
#include "CanBeAttacked.h"
#include "Animator.h"
#include "Macros.h"

ChargeShotController::ChargeShotController(const ChargeShotController& BC) : CMonoBehavior(BC)
{
}

ChargeShotController& ChargeShotController::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	if (const auto pBuster = dynamic_cast<const ChargeShotController*>(&component))
	{
		m_liveTime = pBuster->m_liveTime;
		m_destroyTime = pBuster->m_destroyTime;
	}

	return *this;
}

ChargeShotController::ChargeShotController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

void ChargeShotController::OnTriggerEnter(CCollision* collision)
{
	std::string name = collision->GetOtherCollider()->GetName();
	if(!collision->GetOtherCollider()->GetComponent<CanBeAttacked>() || std::strstr(name.c_str(),"Blast Hornet") || std::strstr(name.c_str(),"Shurikein"))
	{
		m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
		m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
	}
}

void ChargeShotController::Update(const DWORD& dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool(Bool_IsCollision) && anim->GetCurrentAnimation()->IsLastFrame())
	{
		//m_liveTime = 0;
		m_pGameObject->SetIsActive(false);
		return;
	}

	if (m_pGameObject->GetIsActive()) {
		m_liveTime += dt;
		if (m_liveTime > m_destroyTime)
		{
			m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
			m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
			m_pGameObject->GetComponent<CCollider>()->SetIsActive(false);
		}
	}
}

void ChargeShotController::Render()
{
}
