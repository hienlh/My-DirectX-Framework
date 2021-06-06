﻿#include "GenjiBosController.h"

GenjiBosController::GenjiBosController(const GenjiBosController& gen) : CMonoBehavior(gen)
{
	m_light = gen.m_light;
	m_shurikein = gen.m_shurikein;
	m_startTime = gen.m_startTime;
}

GenjiBosController::GenjiBosController(CGameObject * gameObject) :CMonoBehavior(gameObject)
{
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity({ 0,0.1 });
}

void GenjiBosController::Start()
{
	rigid = m_pGameObject->GetComponent<CRigidbody>();
	transform = m_pGameObject->GetComponent<CTransform>();
}

void GenjiBosController::Update(const DWORD &dt)
{
	m_startTime += dt;

	if (m_startTime < 3000)
	{
		if (m_light)
			m_light->SetIsActive(false);
		rigid->SetVelocity({ 0,0.1 });
		if (transform->Get_Position().y > 1140)
		{
			transform->Set_Position({ transform->Get_Position().x,1140 });
			rigid->SetVelocity({ 0,0 });
			m_light->SetIsActive(true);
		}
		
		if (m_startTime > 2500) {
			if (!m_shurikein->GetIsActive())
				m_shurikein->SetIsActive(true);
		}
	}
	else {
		if (m_light)
			m_light->SetIsActive(false);
		rigid->SetVelocity({ 0,-0.1 });

		if (transform->Get_Position().y < 900)
		{
			m_pGameObject->SetIsActive(false);
		}
	}
}
