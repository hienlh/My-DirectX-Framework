#include "BoxController.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"
#include "Macros.h"
#include "BuildingController.h"
#include "CarryAimController.h"

void BoxController::Update(const DWORD& dt)
{
	if(const auto tmp = m_pGameObject->GetComponent<CanBeAttacked>())
	{
		if(!tmp->IsAlive())
		{
			EffectPool::GetInstance()->CreateEffect(Prefab_Effect_Explode, m_pGameObject->GetComponent<Framework::CTransform>()->Get_Position());
			if(auto parent = m_pGameObject->GetParent())
			{
				if(auto building = parent->GetComponent<BuildingController>())
				{
					building->BoxIsDestroy(m_pGameObject);
				}
				
				if(auto carry = parent->GetComponent<CarryAimController>())
				{
					carry->BoxIsDestroyed(m_pGameObject);
				}
			}
			m_pGameObject->SetIsActive(false);
		}
	}
}
