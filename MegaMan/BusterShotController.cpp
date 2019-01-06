#include "BusterShotController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"


BusterShotController::BusterShotController(const BusterShotController& PC) : CMonoBehavior(PC)
{

}

BusterShotController* BusterShotController::Clone()
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

void BusterShotController::Update(DWORD dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool("isCollision") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		//m_pGameObject->SetIsActive(false);
		SAFE_DELETE(m_pGameObject);
	}
}

void BusterShotController::Render()
{

}

