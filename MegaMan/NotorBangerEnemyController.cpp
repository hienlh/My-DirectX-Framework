#include "NotorBangerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"

NotorBangerEnemyController::NotorBangerEnemyController(const NotorBangerEnemyController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
	m_reloadTime = PC.m_reloadTime;
	m_target = PC.m_target;
}

void NotorBangerEnemyController::OnCollisionEnter(CCollision * collision)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	anim->SetBool(Bool_IsJump, false);
}

void NotorBangerEnemyController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	if (m_target)
	{
		const Vector2 targetPosition = m_target->GetComponent<CTransform>()->Get_Position();
		const Vector2 currentPosition = m_pGameObject->GetComponent<CTransform>()->Get_Position();

		if (fabs(targetPosition.x - currentPosition.x) < 200)
		{
			anim->SetBool(Bool_IsJump, false);
			anim->SetBool(Bool_IsIdle, false);

			const DWORD alpha = static_cast<float>(fabs(currentPosition.x - targetPosition.x)) / 3;

			DWORD angles[] = { 0, 30, 45, 60, 90 };
			std::string names[] = { Bool_Is0, Bool_Is30, Bool_Is45, Bool_Is60, Bool_Is90 };
			size_t selectedAngleIndex = 0;
			anim->SetBool(names[0], false);

			// Least angle delta
			for (size_t iAngle = 1; iAngle < _countof(angles); iAngle++)
			{
				anim->SetBool(names[iAngle], false);
				if (fabs(angles[iAngle] - alpha) < fabs(angles[selectedAngleIndex] - alpha))
					selectedAngleIndex = iAngle;
			}
			anim->SetBool(names[selectedAngleIndex], true);

			m_reloadTime += dt;
			if (m_reloadTime >= RELOAD_TIME)
			{
				Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
				const bool isFlip = m_pGameObject->GetComponent<CRenderer>()->GetFlipX();

				pos.x += isFlip ? 10 : -10;
				pos.y -= 20;
				auto pBullet = CGameObject::Instantiate(Prefab_NotorBanger_Bullet, nullptr, pos);

				pBullet->GetComponent<CRigidbody>()->SetVelocity({ (isFlip ? .3f : -.3f) , -.15f });

				float gravity = 0.01*rigidbody->GetGravityScale();
				Vector2 velocity;
				velocity.y = -0.1;
				velocity.x = (((targetPosition.x - currentPosition.x)*gravity) / (-velocity.y + sqrt(pow(velocity.y, 2) - 2 * gravity*(currentPosition.y-targetPosition.y))));
				pBullet->GetComponent<CRigidbody>()->SetVelocity(velocity);
				m_reloadTime = 0;
			}
		}
		else if (fabs(targetPosition.x - currentPosition.x) < 300)
		{
			if (!anim->GetBool(Bool_IsJump))
			{
				anim->SetBool(Bool_IsJump, true);
				anim->SetBool(Bool_IsIdle, false);

				rigidbody->AddVelocity(Vector2((targetPosition.x > currentPosition.x ? .1 : -.1), -.1));
			}
		}
		else
		{
			anim->SetBool(Bool_IsJump, false);
			anim->SetBool(Bool_IsIdle, true);
		}

		renderer->SetFlipX(targetPosition.x > currentPosition.x);
		
	}
}

void NotorBangerEnemyController::Render()
{
}
