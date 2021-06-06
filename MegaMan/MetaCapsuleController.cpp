#include "MetaCapsuleController.h"
#include "Macros.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EffectPool.h"
#include "CanBeAttacked.h"

MetaCapsuleController::MetaCapsuleController(const MetaCapsuleController& monoBehavior)
	: CMonoBehavior(monoBehavior)
{
	m_waitTime = monoBehavior.m_waitTime;
	m_fired = monoBehavior.m_fired;
	player = monoBehavior.player;
}

MetaCapsuleController& MetaCapsuleController::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	if (const auto pMet = dynamic_cast<const MetaCapsuleController*>(&component))
	{
		m_waitTime = pMet->m_waitTime;
		m_fired = pMet->m_fired;
		player = pMet->player;
	}

	return *this;
}

void MetaCapsuleController::Start()
{
	anim = m_pGameObject->GetComponent<Framework::CAnimator>();
	collider = m_pGameObject->GetComponent<Framework::CBoxCollider>();
	transform = m_pGameObject->GetComponent<Framework::CTransform>();

	m_bulletPrefab = Framework::CResourceManager::GetInstance()->GetPrefab(Prefab_MetaCapsule_Bullet);
	m_bullet = Framework::CGameObject::Instantiate(m_bulletPrefab, m_pGameObject, {16,38});
	m_bullet->SetIsActive(false);
}

void MetaCapsuleController::Update(const DWORD& dt)
{
	/*if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition(), 20, 2);
	}*/

	if(anim->GetCurrentAnimation()->IsLastFrame())
	{
		collider->SetIsActive(true);
		if(!m_fired && m_waitTime > 0)
		{
			Fire();
		}
		else if (m_fired && m_waitTime < 0)
		{
			if (!anim->GetBool(Bool_IsOpen)) {
				*m_pGameObject = *Framework::CResourceManager::GetInstance()->GetPrefab(Prefab_MetaCapsule);
				m_pGameObject->SetIsActive(false);
			}
			else if(anim->GetBool(Bool_IsOpen))
				anim->SetBool(Bool_IsOpen, false);
		}
	}

	if (m_fired)
		m_waitTime -= dt;
}

void MetaCapsuleController::Fire()
{
	m_fired = true;

	*m_bullet = *m_bulletPrefab;

	m_bullet->GetComponent<Framework::CTransform>()->Set_Position({ 16,38 }, false);
	m_bullet->SetParent(nullptr);
	auto direction = player->GetPosition() - m_bullet->GetPosition();
	const auto min = min(fabs(direction.x), fabs(direction.y));
	if (min)
		direction = { direction.x / min, direction.y / min };
	
	m_bullet->GetComponent<Framework::CRigidbody>()->SetVelocity(direction * 0.1);
	m_bullet->SetIsActive(true);
}
