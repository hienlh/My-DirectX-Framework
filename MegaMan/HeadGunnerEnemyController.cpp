#include "HeadGunnerEnemyController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

void HeadGunnerEnemyController::OnCollisionEnter(CCollision * collision)
{
}

void HeadGunnerEnemyController::Update(DWORD dt)
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
}

void HeadGunnerEnemyController::Render()
{
}
