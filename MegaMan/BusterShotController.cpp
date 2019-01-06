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

BusterShotController::BusterShotController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void BusterShotController::OnTriggerEnter(CCollision* collision)
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
	m_pGameObject->GetComponent<CCollider>()->SetIsActive(false);
}

void BusterShotController::Update(DWORD dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool(Bool_IsCollision) && anim->GetCurrentAnimation()->IsLastFrame())
	{
		SAFE_DELETE(m_pGameObject);
		return;
	}

	m_liveTime += dt;
	if (m_liveTime > m_destroyTime)
	{
		m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
		m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
		m_pGameObject->GetComponent<CCollider>()->SetIsActive(false);
	}
}

void BusterShotController::Render()
{

}

