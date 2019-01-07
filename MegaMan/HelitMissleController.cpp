#include "HelitMissleController.h"

HelitMissleController::HelitMissleController(const HelitMissleController& PC) : CMonoBehavior(PC)
{
}

HelitMissleController* HelitMissleController::Clone()
{
	return new HelitMissleController(*this);
}

HelitMissleController::HelitMissleController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

HelitMissleController::~HelitMissleController()
{

}

void HelitMissleController::OnTriggerEnter(CCollision* collision)
{

}

void HelitMissleController::Update(DWORD dt)
{
	m_lifeTime -= dt;
	if (m_lifeTime <= 0) SAFE_DELETE(m_pGameObject);
}

void HelitMissleController::Render()
{

}
