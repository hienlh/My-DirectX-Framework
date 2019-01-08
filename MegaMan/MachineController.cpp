#include "MachineController.h"
#include "GameObject.h"
#include "Animator.h"
#include "Macros.h"

void MachineController::OnCollisionEnter(Framework::CCollision* collision)
{
	if (m_pGameObject->GetComponent<Framework::CAnimator>()->GetBool(Bool_IsRun) == false) {
		auto anim = m_pGameObject->GetComponent<Framework::CAnimator>();
		if (collision->CollisionBetween("Player", m_pGameObject->GetName()))
		{
			anim->SetBool(Bool_IsRun, true);
		}
	}
}

void MachineController::Update(const DWORD &dt)
{
	auto anim = m_pGameObject->GetComponent<Framework::CAnimator>();
	auto transform = m_pGameObject->GetComponent<Framework::CTransform>();
	auto rigidBody = m_pGameObject->GetComponent<Framework::CRigidbody>();
	if(anim->GetBool(Bool_IsRun) == true && transform->Get_Position().y > rigidBody->GetLimitedArea().top)
	{
		m_pGameObject->GetComponent<Framework::CTransform>()->Translate(Vector2(0, -.05) * dt);
		//m_player->GetComponent<Framework::CTransform>()->Translate(Vector2(0, -.05) * dt);
	}

	if(transform->Get_Position().y <= rigidBody->GetLimitedArea().top)
	{
		anim->SetBool(Bool_IsRun, false);
	}
}
