#include "BallController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "BoxCollider.h"
#include "Input.h"
#include "Animator.h"

BallController::BallController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void BallController::SetState(int state)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	switch (state)
	{
	case JUMP:
		if((m_state & JUMP) != JUMP){
			rigidbody->SetVelocity(Vector2(0, -.1));
			m_state &= ~State::IDLE;
			m_state |= State::JUMP;
		}
		break; 
	case ~JUMP:
		rigidbody->SetVelocity(Vector2(NULL, 0));
		break;
	case MOVE_RIGHT:
		anim->SetCurrentAnimation(L"Mario Walk Right");
		rigidbody->SetVelocity(.1, NULL);

		m_state &= ~State::MOVE_LEFT;
		m_state |= State::MOVE_RIGHT;
		break;
	case ~MOVE_RIGHT:
		anim->SetCurrentAnimation(L"Mario Idle Right");
		rigidbody->SetVelocity(0);
		m_state &= ~State::MOVE_RIGHT;
		break;
	case MOVE_LEFT:
		anim->SetCurrentAnimation(L"Mario Walk Left");
		rigidbody->SetVelocity(-.1);

		m_state &= ~State::MOVE_RIGHT;
		m_state |= State::MOVE_LEFT;
		break;
	case ~MOVE_LEFT:
		anim->SetCurrentAnimation(L"Mario Idle Left");
		rigidbody->SetVelocity(0);
		m_state &= ~State::MOVE_LEFT;
		break;
	case MOVE_DOWN:
		rigidbody->SetVelocity(NULL,.1);
		break;
	case ~MOVE_DOWN:
		rigidbody->SetVelocity(NULL, 0);
		break;
	case IDLE:
		if((m_state & MOVE_RIGHT) == MOVE_RIGHT)
			anim->SetCurrentAnimation(L"Mario Idle Right");
		else if((m_state & MOVE_LEFT) == MOVE_LEFT)
			anim->SetCurrentAnimation(L"Mario Idle Left");
		rigidbody->SetVelocity(Vector2(0, 0));

		m_state &= ~State::JUMP;
		m_state &= ~State::MOVE_LEFT;
		m_state &= ~State::MOVE_RIGHT;
		m_state |= State::IDLE;
		break;
	}

	//CDebug::Log("Current State: %d\n", m_state);
}

void BallController::OnCollisionEnter(CCollision* collision)
{
	//CDebug::Log("Collision ground \n");
	SetState(IDLE);
}

void BallController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();

	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_UPARROW)) {
		//CDebug::Log("Jump \n");
		SetState(JUMP);
	}
	if (input->KeyUp(DIK_UPARROW)) {
		//CDebug::Log("Jump \n");
		SetState(~JUMP);
	}


	if (input->KeyDown(DIK_LEFTARROW)) {
		//CDebug::Log("Move Left \n");
		SetState(MOVE_LEFT);
	}
	if (input->KeyUp(DIK_LEFTARROW)) {
		//CDebug::Log("UnMove Left \n");
		SetState(~MOVE_LEFT);
	}

	if (input->KeyDown(DIK_RIGHTARROW)) {
		//CDebug::Log("Move Right \n");
		SetState(MOVE_RIGHT);
	}
	if (input->KeyUp(DIK_RIGHTARROW)) {
		//CDebug::Log("UnMove Right \n");
		SetState(~MOVE_RIGHT);
	}

	if(input->KeyDown(DIK_DOWNARROW))
	{
		SetState(MOVE_DOWN);
	}
	if (input->KeyUp(DIK_DOWNARROW))
	{
		SetState(~MOVE_DOWN);
	}

	if (rigidbody->GetVelocity() == Vector2(0, 0) && m_state != IDLE)
	{
		SetState(IDLE);
	}
}

void BallController::Render()
{
}
