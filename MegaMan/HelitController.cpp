#include "HelitController.h"
#include "Renderer.h"
#include "Macros.h"
#include "EffectPool.h"
#include "CanBeAttacked.h"

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

HelitController* HelitController::SetLimitDistance(const int& distance)
{
	float pos = (m_limitBottom + m_limitTop) / 2;
	if (m_limitBottom == m_limitTop && m_limitTop == 0) 
		pos = m_pGameObject->GetPosition().x;

	m_limitBottom = pos + distance / 2;

	return this;
}

HelitController::HelitController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

void HelitController::Start()
{
	transform = m_pGameObject->GetComponent<CTransform>();
	renderer = m_pGameObject->GetComponent<CRenderer>();
	rigid = m_pGameObject->GetComponent<CRigidbody>();

	rigid->SetVelocity({ 0, .02 });
	SetLimitDistance();
}

void HelitController::OnTriggerEnter(CCollision * collision)
{

}

void HelitController::Update(const DWORD &dt)
{
	if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition(), 20, 2);
	}

	renderer->SetFlipX(m_target->GetPosition().x > transform->Get_Position().x);

	if(transform->Get_Position().x > m_limitBottom)
	{
		rigid->SetVelocity({ 0, -.02 });
	}
	else if (transform->Get_Position().x < m_limitTop)
	{
		rigid->SetVelocity({ 0, .02 });
	}

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