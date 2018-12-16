#include "ShurikeinController.h"



ShurikeinController::ShurikeinController(CGameObject * gameObject) :CMonoBehavior(gameObject)
{
}


ShurikeinController::~ShurikeinController()
{
}

void ShurikeinController::Update(DWORD dt)
{
	auto rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	auto transform = m_pGameObject->GetComponent<CTransform>();
	
	/*if (GetTickCount() - m_startTimeShurikein > 5000)
	{
		if (!m_shurikein)
			m_shurikein->SetIsActive(true);
	}*/
}

void ShurikeinController::Render()
{
}