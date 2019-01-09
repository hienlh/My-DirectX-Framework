#include "BoxEndController.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"

void BoxEndController::Update(const DWORD& dt)
{
	if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(
			Prefab_Effect_Explode, m_pGameObject->GetComponent<Framework::CBoxCollider>()->GetBoundGlobal(), 10);
	}
}
