#include "NotorBangerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

void NotorBangerEnemyController::OnCollisionEnter(CCollision * collision)
{
	/*CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	rigidbody->AddVelocity(Vector2(0, 0));*/

	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	anim->SetBool("isJump", false);
}

void NotorBangerEnemyController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	const Vector2 velocity = rigidbody->GetVelocity();

	//OutputDebugStringA((std::to_string(anim->GetBool("isIdle")) + " " + std::to_string(anim->GetBool("isJump")) + "\n").c_str());

	CInput *input = CInput::GetInstance();

	if (m_target)
	{
		Vector2 targetPosition = m_target->GetComponent<CTransform>()->Get_Position();
		Vector2 currentPosition = m_pGameObject->GetComponent<CTransform>()->Get_Position();

		if (fabs(targetPosition.x - currentPosition.x) < 200)
		{
			anim->SetBool("isJump", false);
			anim->SetBool("isIdle", false);

			DWORD alpha = (float)fabs(currentPosition.x - targetPosition.x) / 3;
			OutputDebugStringA(((std::to_string(alpha) + "\n").c_str()));

			DWORD angles[] = { 0, 30, 45, 60, 90 };
			std::string names[] = { "is0", "is30", "is45", "is60", "is90" };
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
			OutputDebugStringA((names[selectedAngleIndex] + "\n").c_str());

		}
		else if (fabs(targetPosition.x - currentPosition.x) < 300)
		{
			if (!anim->GetBool("isJump"))
			{
				anim->SetBool("isJump", true);
				anim->SetBool("isIdle", false);
				OutputDebugStringA("Jump");

				rigidbody->AddVelocity(Vector2((targetPosition.x > currentPosition.x ? .1 : -.1), -.1));
			}
		}
		else
		{
			anim->SetBool("isJump", false);
			anim->SetBool("isIdle", true);
		}

		/*if (input->ButtonDown(DIK_SPACE))
		{
			anim->SetBool("isJump", true);
			anim->SetBool("isIdle", false);
			OutputDebugStringA("Jump");

			rigidbody->AddVelocity(Vector2(.1, -.3));
		}*/

		renderer->SetFlipX(targetPosition.x > currentPosition.x);
	}
}

void NotorBangerEnemyController::Render()
{
}
