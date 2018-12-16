#include "BusterShotController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"


BusterShotController::BusterShotController(const BusterShotController& PC) : CMonoBehavior(PC)
{

}

BusterShotController* BusterShotController::Clone() const
{
	return new BusterShotController(*this);
}

BusterShotController::BusterShotController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void BusterShotController::OnTriggerEnter(CCollision* collision)
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool("isCollision", true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
}

void BusterShotController::OnCollisionEnter(CCollision* collision)
{
	// CDebug::Log(collision->GetColliderName());
	// CDebug::Log(collision->GetOtherColliderName());
	// CDebug::Log(m_pGameObject->GetName());
	// CDebug::Log("\n");
	m_pGameObject->GetComponent<CAnimator>()->SetBool("isCollision", true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
		
}

void BusterShotController::Update(DWORD dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool("isCollision") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		m_pGameObject->SetIsActive(false);
	}
}

void BusterShotController::Render()
{

}

