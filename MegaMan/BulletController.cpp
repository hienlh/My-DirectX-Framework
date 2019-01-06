#include "BulletController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"
#include "Macros.h"
#include "PlayerController.h"

BulletController::BulletController(const BulletController& BC) : CMonoBehavior(BC)
{
	m_liveTime = BC.m_liveTime;
}

void BulletController::OnTriggerEnter(CCollision * collision)
{
	m_pGameObject->GetComponent<CAnimator>()->SetBool(Bool_IsCollision, true);
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0 });
}

void BulletController::Update(DWORD dt)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	if (anim->GetBool(Bool_IsCollision) && anim->GetCurrentAnimation()->IsLastFrame()) {
		SAFE_DELETE(m_pGameObject);
		return;
	}

	m_liveTime += dt;
	if (m_liveTime > DESTROY_TIME)
	{
		anim->SetBool(Bool_IsCollision, true);
		m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(VECTOR2_ZERO);
		m_liveTime = 0;
	}
}

void BulletController::Render()
{
}
