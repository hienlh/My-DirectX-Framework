#include "DoorController.h"
#include "PlayerController.h"
#include "Macros.h"
#include "GameManager.h"
#include "CanBeAttacked.h"

void DoorController::Start()
{
	anim = m_pGameObject->GetComponent<CAnimator>();
	collider = m_pGameObject->GetComponent<CBoxCollider>();
}

void DoorController::OnTriggerEnter(Framework::CCollision* collision)
{
	auto gameObject = collision->GetOtherCollider();
	if(strstr(gameObject->GetName().c_str(), std::string("Player").c_str()))
	{
		if(auto playerController = gameObject->GetComponent<PlayerController>())
		{
			playerController->SetCanMove(false);
			playerController->SetCanAction(false);
		}

		anim->SetBool(Bool_IsOpen, true);
		gameObject->GetComponent<CAnimator>()->GetCurrentAnimation()->SetSpeed(0);
		m_target = gameObject;
		
		auto mainCam = CGameManager::GetInstance()->GetCurrentScene()->GetMainCamera()->GetComponent<CameraController>();
		if(mainCam->GetState() == CameraState::MeetingBoss)
			mainCam->SetState(CameraState::Following);
		else
			mainCam->SetState(CameraState::MeetingBoss);
	}
}

void DoorController::Update(const DWORD &dt)
{
	if(m_target)
	{
		if (anim->GetCurrentAnimation()->IsLastFrame()) 
		{
			auto targetTransform = m_target->GetComponent<CTransform>();
			targetTransform->Translate(Vector2(0.1, 0) * dt);

			if (m_target->GetComponent<CBoxCollider>()->GetBoundGlobal().left > collider->GetBoundGlobal().right)
			{
				m_target->GetComponent<CAnimator>()->GetCurrentAnimation()->SetSpeed(1);
				if (auto playerController = m_target->GetComponent<PlayerController>())
				{
					playerController->SetCanMove(true);
					playerController->SetCanAction(true);
				}
				m_target = nullptr;
				collider->SetIsTrigger(false);
				anim->SetBool(Bool_IsOpen, false);
			}
		}
	}

	if(pBoss)
	{
		if(const auto bossHealth = pBoss->GetComponent<CanBeAttacked>())
		{
			if(!bossHealth->IsAlive())
			{
				collider->SetIsTrigger(true);
			}
		}
	}
}

