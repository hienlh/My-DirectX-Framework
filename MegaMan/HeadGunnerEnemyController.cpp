#include "HeadGunnerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"
#include "BulletPool.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"

HeadGunnerEnemyController::HeadGunnerEnemyController(const HeadGunnerEnemyController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
	m_reloadTime = PC.m_reloadTime;
	m_target = PC.m_target;
}

HeadGunnerEnemyController& HeadGunnerEnemyController::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if(const auto pHead = dynamic_cast<const HeadGunnerEnemyController*>(&component))
	{
		m_speed = pHead->m_speed;
		m_reloadTime = pHead->m_reloadTime;
		m_target = pHead->m_target;
	}

	return *this;
}

void HeadGunnerEnemyController::OnCollisionEnter(CCollision * collision)
{
}

void HeadGunnerEnemyController::Update(const DWORD &dt)
{
	if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition(), 20, 2);
	}

	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	if (m_target)
	{
		const Vector2 targetPosition = m_target->GetComponent<CTransform>()->Get_Position();
		const Vector2 currentPosition = transform->Get_Position();

		if (sqrt(pow(targetPosition.x - currentPosition.x, 2)) < 200)
		{
			renderer->SetFlipX(targetPosition.x > currentPosition.x);

			m_reloadTime += dt;
			if (m_reloadTime >= RELOAD_TIME)
			{
				anim->SetBool(Bool_IsShoot, true);

				Vector2 pos = currentPosition;
				const bool isFlip = renderer->GetFlipX();

				pos.x += isFlip ? 10 : -10;
				//auto pBullet = CGameObject::Instantiate(Prefab_BusterShot_Bullet, nullptr, pos);
				auto pBullet = BulletPool::GetInstance()->CreateBullet(Prefab_BusterShot_Bullet, pos);
				pBullet->GetComponent<CRigidbody>()->SetVelocity({ (isFlip ? .3f : -.3f) , 0 });

				m_reloadTime = 0;
			}
		}

		if(anim->GetBool(Bool_IsShoot) && anim->GetCurrentAnimation()->IsLastFrame())
			anim->SetBool(Bool_IsShoot, false);
	}
}

void HeadGunnerEnemyController::Render()
{
}
