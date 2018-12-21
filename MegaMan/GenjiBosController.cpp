#include "GenjiBosController.h"

GenjiBosController::GenjiBosController(CGameObject * gameObject) :CMonoBehavior(gameObject)
{
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0.1 });
}

GenjiBosController::~GenjiBosController()
{
}

void GenjiBosController::Update(DWORD dt)
{
	m_startTime += dt;
	auto rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	auto transform = m_pGameObject->GetComponent<CTransform>();

	if (m_startTime > 3000) {
		if (m_shurikein)
			m_shurikein->SetIsActive(true);
	}

	if (m_startTime < 5000)
	{
		if (m_light)
			m_light->SetIsActive(false);
		rigidbody->SetVelocity({ 0,0.1 });
		if (transform->Get_Position().y > 1140)
		{
			transform->Set_Position({ transform->Get_Position().x,1140 });
			rigidbody->SetVelocity({ 0,0 });
			m_light->SetIsActive(true);
		}
	}
	else {
		if (m_light)
			m_light->SetIsActive(false);
		rigidbody->SetVelocity({ 0,-0.1 });
	}
}

void GenjiBosController::Render()
{
}
