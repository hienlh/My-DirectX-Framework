#include "BulletController.h"
#include "Animation.h"
#include "GameObject.h"
#include "Animator.h"
#include "Macros.h"
#include "PlayerController.h"
#include "EffectPool.h"

BulletController::BulletController(const BulletController& BC) : CMonoBehavior(BC)
{
	m_liveTime = BC.m_liveTime;
	m_currentWaitTime = BC.m_currentWaitTime;
	m_waitForCreateSmoke = BC.m_waitForCreateSmoke;
}

BulletController& BulletController::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	if(const auto pBullet = dynamic_cast<const BulletController*>(&component))
	{
		m_currentWaitTime = pBullet->m_currentWaitTime;
		m_liveTime = pBullet->m_liveTime;
		m_waitForCreateSmoke = pBullet->m_waitForCreateSmoke;
	}

	return *this;
}

void BulletController::OnTriggerEnter(CCollision * collision)
{
	m_pGameObject->SetIsActive(false);
}

void BulletController::Update(const DWORD &dt)
{
	SmokeEffect(dt);

	m_liveTime += dt;
	if (m_liveTime > DESTROY_TIME)
	{
		m_liveTime = 0;
		EffectPool::GetInstance()->CreateEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition());
		m_pGameObject->SetIsActive(false);
	}
}

void BulletController::Render()
{
}

void BulletController::SmokeEffect(const DWORD &dt)
{
	m_currentWaitTime += dt;
	if (m_currentWaitTime > m_waitForCreateSmoke)
	{
		EffectPool::GetInstance()->CreateEffect(Prefab_Effect_Smoke, m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position());
		m_currentWaitTime = 0;
	}
}
