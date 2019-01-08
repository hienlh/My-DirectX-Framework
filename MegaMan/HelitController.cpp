#include "HelitController.h"
#include "Renderer.h"
#include "Macros.h"

HelitController::HelitController(const HelitController& PC) : CMonoBehavior(PC)
{
	m_missleVelocity = PC.m_missleVelocity;
	m_reloadTime = PC.m_reloadTime;
}

HelitController* HelitController::Clone()
{
	return new HelitController(*this);
}

HelitController& HelitController::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if (const auto pHelit = dynamic_cast<const HelitController*>(&component)) {
		m_missleVelocity = pHelit->m_missleVelocity;
		m_reloadTime = pHelit->m_reloadTime;
	}

	return *this;
}

HelitController::HelitController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

void HelitController::Start()
{
	transform = m_pGameObject->GetComponent<CTransform>();
	renderer = m_pGameObject->GetComponent<CRenderer>();
}

void HelitController::OnTriggerEnter(CCollision * collision)
{

}

void HelitController::Update(const DWORD &dt)
{
	m_reloadTime -= dt;
	Vector2 velocity;
	if (m_reloadTime <= 0)
	{
		auto missle = CGameObject::Instantiate(Prefab_Helit_Missle, nullptr, transform->Get_Position() + Vector2(0, 10));
		if (!renderer->GetFlipX())
		{
			velocity.x = -m_missleVelocity.x;
			velocity.y = m_missleVelocity.y;
			missle->GetComponent<CRenderer>()->SetFlipX(false);
		}
		else
		{
			velocity.x = m_missleVelocity.x;
			velocity.y = m_missleVelocity.y;
			missle->GetComponent<CRenderer>()->SetFlipX(true);
		}
		missle->GetComponent<CRigidbody>()->SetVelocity(velocity);
		m_reloadTime = 2000;
	}
}