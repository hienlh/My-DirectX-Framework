#include "BusterShotController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"
#include "Macros.h"


BusterShotController::BusterShotController(const BusterShotController& BC) : CMonoBehavior(BC)
{
	m_liveTime = BC.m_liveTime;
	m_destroyTime = BC.m_destroyTime;
}

BusterShotController& BusterShotController::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	if(const auto pBuster = dynamic_cast<const BusterShotController*>(&component))
	{
		m_liveTime = pBuster->m_liveTime;
		m_destroyTime = pBuster->m_destroyTime;
	}

	return *this;
}

BusterShotController::BusterShotController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void BusterShotController::OnTriggerEnter(CCollision* collision)
{
	if (!m_pGameObject->GetComponent<CAnimator>()->GetBool(Bool_IsCollision)) 
	{
		m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
		m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
		m_pGameObject->GetComponent<CCollider>()->SetIsActive(false);
	}
}

void BusterShotController::Update(const DWORD &dt)
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

void BusterShotController::Render()
{

}

