#include "NotorBangerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

void NotorBangerEnemyController::OnCollisionEnter(CCollision * collision)
{
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

	if (input->KeyDown(DIK_L))
	{
		anim->SetBool("isIdle", false);
		anim->SetBool("isJump", true);
	}

	if (m_target)
	{
		/*Vector2 targetPosition = m_target->GetComponent<CTransform>()->Get_Position();
		Vector2 currentPosition = m_pGameObject->GetComponent<CTransform>()->Get_Position();

		float d = (currentPosition.x - targetPosition.x) / 5;
		OutputDebugStringA(((std::to_string(d) + "\n").c_str()));
		
		DWORD distances[] = { 0, 30, 45, 60, 90 };
		for (DWORD distance : distances)
			if (fabs(distance - d) < )
*/
	}
}

void NotorBangerEnemyController::Render()
{
}
