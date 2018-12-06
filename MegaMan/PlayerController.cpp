#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

PlayerController::PlayerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void PlayerController::UpdateState(DWORD stateCode, bool flag)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CAnimator *animation = m_pGameObject->GetComponent<CAnimator>();
	
	// ON
	if (flag)
		m_stateCode |= stateCode;
	// OFF
	else
		m_stateCode &= ~stateCode;

	switch (m_stateCode)
	{
	case S_IDLE:
		animation->SetCurrentState(L"Megaman Idle");
		break;
	
	case S_RUN:
		animation->SetCurrentState(L"Megaman Run");
		break;

	case S_JUMP:
		animation->SetCurrentState(L"Megaman Jump");
		//OutputDebugStringW(L"Jump");
		break;

	case S_FALL:
		animation->SetCurrentState(L"Megaman Fall");
		break;

	case S_IDLE_SHOOT:
		animation->SetCurrentState(L"Megaman Idle Shoot");
		OutputDebugStringW(L"Shoot\n");
		break;
	}

	//m_pGameObject->GetComponent<CAnimator>()->SetStateCode(m_stateCode);
}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	CDebug::Log("Collision ground \n");
	UpdateState(IDLE, true);
	UpdateState(RUN, false);
	UpdateState(JUMP, false);
	UpdateState(FALL, false);
}

void PlayerController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	CInput *input = CInput::GetInstance();

	// SPACE 
	if (input->KeyDown(DIK_SPACE))
	{
		rigidbody->SetVelocity(Vector2(0, -.3));
		UpdateState(JUMP, true);
		UpdateState(IDLE, false);
		UpdateState(RUN, false);
		UpdateState(FALL, false);
	}

	// LEFT
	if (input->KeyDown(DIK_LEFT))
	{
		m_pGameObject->GetComponent<CRenderer>()->SetFlipX(true);
		rigidbody->SetVelocity(Vector2(-0.3, 0));
		UpdateState(RUN, true);
		UpdateState(IDLE, false);
	}
	
	// RIGHT
	if (input->KeyDown(DIK_RIGHT))
	{
		m_pGameObject->GetComponent<CRenderer>()->SetFlipX(false);
		rigidbody->SetVelocity(Vector2(0.3, 0));
		UpdateState(RUN, true);
		UpdateState(IDLE, false);
	}

	if (input->KeyUp(DIK_LEFT) || input->KeyUp(DIK_RIGHT))
	{
		rigidbody->SetVelocity(Vector2(0, 0));
		UpdateState(RUN, false);
		UpdateState(IDLE, true);
	}

	if (input->KeyDown(DIK_RETURN))
	{
		UpdateState(SHOOT, true);
		UpdateState(IDLE, true);
		UpdateState(RUN, false);
		UpdateState(JUMP, false);
		UpdateState(FALL, false);
	}

	if (input->KeyUp(DIK_RETURN))
	{
		UpdateState(SHOOT, false);
	}
	// SHOOT
	/*if (input->KeyDown(DIK_RETURN))
		UpdateState(EState::SHOOT);
	
	if (input->KeyUp(DIK_RIGHT))
		UpdateState(~EState::SHOOT);*/
}

void PlayerController::Render()
{
}
