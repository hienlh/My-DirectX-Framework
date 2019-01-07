#include "HelitController.h"
#include "Renderer.h"
#include "Macros.h"

HelitController::HelitController(const HelitController& PC) : CMonoBehavior(PC)
{

}

HelitController* HelitController::Clone()
{
	return new HelitController(*this);
}

HelitController::HelitController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{
}

HelitController::~HelitController()
{
}

void HelitController::OnTriggerEnter(CCollision * collision)
{

}

void HelitController::Update(DWORD dt)
{
	auto transform = m_pGameObject->GetComponent<CTransform>();
	auto renderer = m_pGameObject->GetComponent<CRenderer>();
	m_reloadTime -= dt;
	Vector2 velocity;
	if(m_reloadTime <= 0)
	{
		auto missle = CGameObject::Instantiate(Prefab_Helit_Missle, nullptr, transform->Get_Position() + Vector2(0,10));
		if (renderer->GetFlipX() == false)
		{
			velocity.x = -m_missleVelocity.x;
			velocity.y = m_missleVelocity.y;
			missle->GetComponent<CRenderer>()->SetFlipX(false);
		}else
		{
			velocity.x = m_missleVelocity.x;
			velocity.y = m_missleVelocity.y;
			missle->GetComponent<CRenderer>()->SetFlipX(true);
		}
		missle->GetComponent<CRigidbody>()->SetVelocity(velocity);
		m_reloadTime = 2000;
	}
}

void HelitController::Render()
{
}
