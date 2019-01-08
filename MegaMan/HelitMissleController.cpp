#include "HelitMissleController.h"

HelitMissleController::HelitMissleController(const HelitMissleController& PC) : CMonoBehavior(PC)
{
	m_lifeTime = PC.m_lifeTime;
}

HelitMissleController* HelitMissleController::Clone()
{
	return new HelitMissleController(*this);
}

HelitMissleController& HelitMissleController::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if (const auto pHelit = dynamic_cast<const HelitMissleController*>(&component)) {
		m_lifeTime = pHelit->m_lifeTime;
	}

	return *this;
}

HelitMissleController::HelitMissleController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void HelitMissleController::Start()
{
}

void HelitMissleController::OnTriggerEnter(CCollision* collision)
{

}

void HelitMissleController::Update(const DWORD &dt)
{
	m_lifeTime -= dt;
	if (m_lifeTime <= 0) m_pGameObject->SetIsActive(false);
}