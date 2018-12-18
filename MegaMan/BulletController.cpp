#include "BulletController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"

void BulletController::OnTriggerEnter(CCollision * collision)
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool(BoolCollision, true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
}

void BulletController::Update(DWORD dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool(BoolCollision) && anim->GetCurrentAnimation()->IsLastFrame())
		SAFE_DELETE(m_pGameObject);

	m_liveTime += dt;
	if (m_liveTime > DESTROY_TIME)
	{
		//anim->SetBool(BoolCollision, true);
		//m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(VECTOR2_ZERO);
	}
}

void BulletController::Render()
{
}
