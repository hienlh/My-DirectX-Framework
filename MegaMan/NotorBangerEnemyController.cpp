#include "NotorBangerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Animator.h"
#include "Macros.h"
#include "Renderer.h"
#include "BulletPool.h"
#include "CanBeAttacked.h"
#include "EffectPool.h"

NotorBangerEnemyController::NotorBangerEnemyController(const NotorBangerEnemyController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
	m_reloadTime = PC.m_reloadTime;
	m_target = PC.m_target;
}

NotorBangerEnemyController& NotorBangerEnemyController::operator=(const CComponent& component)

{
	(*this).CMonoBehavior::operator=(component);

	if (const auto pNotor = dynamic_cast<const NotorBangerEnemyController*>(&component))
	{
		m_speed = pNotor->m_speed;
		m_reloadTime = pNotor->m_reloadTime;
		m_target = pNotor->m_target;
	}

	return *this;
}

Vector2 NotorBangerEnemyController::CalculateVelocity(const Vector2& myPosition, const Vector2& targetPosition,
	const float& gravity, const float& vy) const
{
	Vector2 velocity;
	velocity.y = vy;
	float time = (-velocity.y + sqrt(pow(velocity.y, 2) - 2 * gravity*(myPosition.y - targetPosition.y))) / gravity;
	velocity.x = (((targetPosition.x - myPosition.x)) / time);
	return velocity;
}

std::string NotorBangerEnemyController::CalculateAngelRotation(const Vector2& velocity) const
{
	const float alpha = fabs(velocity.y / sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)));
	float angles[] = { 0, 0.5, 1 / sqrt(2), sqrt(3) / 2, 1 };
	std::string names[] = { Bool_Is0, Bool_Is30, Bool_Is45, Bool_Is60, Bool_Is90 };
	size_t selectedAngleIndex = 0;

	// Least angle delta
	for (size_t iAngle = 1; iAngle < _countof(angles); iAngle++)
	{
		if (fabs(angles[iAngle] - alpha) < fabs(angles[selectedAngleIndex] - alpha))
			selectedAngleIndex = iAngle;
	}
	return names[selectedAngleIndex];
}

void NotorBangerEnemyController::OnCollisionEnter(CCollision * collision)
{
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	anim->SetBool(Bool_IsJump, false);
}

void NotorBangerEnemyController::Update(const DWORD &dt)
{
	if (!m_pGameObject->GetComponent<CanBeAttacked>()->IsAlive())
	{
		m_pGameObject->SetIsActive(false);
		EffectPool::GetInstance()->CreateMultiEffect(Prefab_Effect_Explode, m_pGameObject->GetPosition(), 20, 2);
		CGameObject::Instantiate(Prefab_SmallHeath_Item, nullptr, m_pGameObject->GetPosition());
	}

	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	if (m_target)
	{
		const Vector2 targetPosition = m_target->GetComponent<CTransform>()->Get_Position();
		const Vector2 currentPosition = m_pGameObject->GetComponent<CTransform>()->Get_Position();

		const float gravity = 0.001*rigidbody->GetGravityScale();
		const Vector2 velocity = CalculateVelocity(currentPosition, targetPosition, gravity, -0.3);
		std::string names[] = { Bool_Is0, Bool_Is30, Bool_Is45, Bool_Is60, Bool_Is90 };
		for (size_t iAngle = 0; iAngle < _countof(names); iAngle++)
		{
			anim->SetBool(names[iAngle], false);
		}
		anim->SetBool(CalculateAngelRotation(velocity), true);

		if (fabs(targetPosition.x - currentPosition.x) < 200)
		{
			anim->SetBool(Bool_IsJump, false);
			anim->SetBool(Bool_IsIdle, false);

			// const DWORD alpha = static_cast<float>(fabs(currentPosition.x - targetPosition.x)) / 3;
			//
			// DWORD angles[] = { 0, 30, 45, 60, 90 };
			// std::string names[] = { Bool_Is0, Bool_Is30, Bool_Is45, Bool_Is60, Bool_Is90 };
			// size_t selectedAngleIndex = 0;
			// anim->SetBool(names[0], false);
			//
			// // Least angle delta
			// for (size_t iAngle = 1; iAngle < _countof(angles); iAngle++)
			// {
			// 	anim->SetBool(names[iAngle], false);
			// 	if (fabs(angles[iAngle] - alpha) < fabs(angles[selectedAngleIndex] - alpha))
			// 		selectedAngleIndex = iAngle;
			// }
			//

			m_reloadTime += dt;
			if (m_reloadTime >= RELOAD_TIME)
			{
				Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
				const bool isFlip = m_pGameObject->GetComponent<CRenderer>()->GetFlipX();

				// pos.x += isFlip ? 10 : -10;
				// pos.y -= 20;
				auto pBullet = CGameObject::Instantiate(Prefab_NotorBanger_Bullet, nullptr, pos);
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
