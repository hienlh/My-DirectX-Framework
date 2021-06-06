#include "SpawnEndBoxController.h"
#include "Macros.h"

void SpawnEndBoxController::Update(const DWORD& dt)
{
	m_waitTime -= dt;
	if(!target->GetIsActive())
	{
		if(m_waitTime<0)
		{
			Framework::CGameObject::Instantiate(Prefab_BoxEnd, nullptr, m_pGameObject->GetPosition());
			m_waitTime = WAIT_TIME;
		}
	}
}
