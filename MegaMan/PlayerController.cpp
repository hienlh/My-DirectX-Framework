#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

PlayerController::PlayerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void PlayerController::SetState(int state)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	
	switch (state)
	{
	case JUMP:
		if((m_state & JUMP) != JUMP)
		{
			rigidbody->SetVelocity(Vector2(0, -.3));
			m_state &= ~State::IDLE;
			m_state |= State::JUMP;
		}
		break;

	case MOVE_RIGHT:
		anim->SetCurrentAnimation(L"Megaman Run Right");
		rigidbody->SetVelocity(.12, NULL);

		m_state &= ~State::MOVE_LEFT;
		m_state |= State::MOVE_RIGHT;
		break;

	case ~MOVE_RIGHT:
		anim->SetCurrentAnimation(L"Megaman Idle Right");
		rigidbody->SetVelocity(0);
		m_state &= ~State::MOVE_RIGHT;
		break;

	case MOVE_LEFT:
		anim->SetCurrentAnimation(L"Megaman Run Left");
		rigidbody->SetVelocity(-.12, NULL);

		m_state &= ~State::MOVE_RIGHT;
		m_state |= State::MOVE_LEFT;
		break;

	case ~MOVE_LEFT:
		anim->SetCurrentAnimation(L"Megaman Idle Left");
		rigidbody->SetVelocity(0);
		m_state &= ~State::MOVE_LEFT;
		break;

	case IDLE:
		if ((m_state & MOVE_RIGHT) == MOVE_RIGHT)
			anim->SetCurrentAnimation(L"Megaman Idle Right");
		if ((m_state & MOVE_LEFT) == MOVE_LEFT)
			anim->SetCurrentAnimation(L"Megaman Idle Left");
		
		rigidbody->SetVelocity(Vector2(0, 0));
		m_state &= ~State::JUMP;
		m_state &= ~State::MOVE_LEFT;
		m_state &= ~State::MOVE_RIGHT;
		m_state |= State::IDLE;
		break;
	}

	CDebug::Log("Current State: %d\n", m_state);
}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	CDebug::Log("Collision ground \n");
	SetState(IDLE);
}

void PlayerController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_W) || input->KeyDown(DIK_UP)) 
	{
		CDebug::Log("Jump \n");
		SetState(JUMP);
	}

	if (input->KeyDown(DIK_A) || input->KeyDown(DIK_LEFT)) 
	{
		CDebug::Log("Move Left \n");
		SetState(MOVE_LEFT);
	}
	
	if (input->KeyUp(DIK_A) || input->KeyUp(DIK_LEFT)) 
	{
		CDebug::Log("UnMove Left \n");
		SetState(~MOVE_LEFT);
	}

	if (input->KeyDown(DIK_D) || input->KeyDown(DIK_RIGHT)) 
	{
		CDebug::Log("Move Right \n");
		SetState(MOVE_RIGHT);
	}
	
	if (input->KeyUp(DIK_D) || input->KeyUp(DIK_RIGHT)) 
	{
		CDebug::Log("UnMove Right \n");
		SetState(~MOVE_RIGHT);
	}
}

void PlayerController::Render()
{
}
