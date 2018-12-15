#include "MachineController.h"
#include "GameObject.h"
#include "Animator.h"

void MachineController::OnCollisionEnter(Framework::CCollision* collision)
{
	if (m_pGameObject->GetComponent<Framework::CAnimator>()->GetBool("isRun") == false) {
		auto anim = m_pGameObject->GetComponent<Framework::CAnimator>();
		if (collision->CollisionBetween("Player", m_pGameObject->GetName()))
		{
			anim->SetBool("isRun", true);
		}
	}
}

void MachineController::Update(DWORD dt)
{
	auto anim = m_pGameObject->GetComponent<Framework::CAnimator>();
	if(anim->GetBool("isRun") == true)
	{
		m_pGameObject->GetComponent<Framework::CTransform>()->Translate(Vector2(0, -.1) * dt);
	}
}
