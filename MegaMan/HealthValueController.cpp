#include "HealthValueController.h"
#include "CanBeAttacked.h"

HealthValueController::HealthValueController(const HealthValueController& hv)
	: CMonoBehavior(hv)
{
	m_target = hv.m_target;
	m_preRatio = hv.m_preRatio;
}

void HealthValueController::Update(const DWORD &dt)
{
	if(m_target)
		if(const auto canBeAttacked = m_target->GetComponent<CanBeAttacked>())
		{
			const float currentHealth = canBeAttacked->GetCurrentHealth();
			const float maxHealth = canBeAttacked->GetMaxHealth();
			const float ratio = currentHealth / maxHealth;

			if(m_preRatio != ratio)
				if(const auto renderer = m_pGameObject->GetComponent<Framework::CRenderer>())
				{
					Vector2 size = renderer->GetSprite()->GetRootSourceRect().Size();
					size.y *= ratio;
					renderer->GetSprite()->SetSize(size);
					m_preRatio = ratio;
				}
		}
}
