#include "HealItemController.h"

void HealItemController::OnCollisionEnter(Framework::CCollision* collision)
{
	
}

void HealItemController::Update(const DWORD& dt)
{
	if (isCollision) SAFE_DELETE(m_pGameObject);
}
