#include "HealItemController.h"
#include "CanBeAttacked.h"

void HealItemController::OnCollisionEnter(Framework::CCollision* collision)
{
	if(auto a = collision->GetOtherCollider()->GetComponent<CanBeAttacked>())
	{
		a->Heal(m_healValue);
		m_pGameObject->SetIsActive(false);
	}
}

void HealItemController::Update(const DWORD& dt)
{
}
