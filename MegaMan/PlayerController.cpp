#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "BoxCollider.h"
#include "Input.h"
#include "Animator.h"

PlayerController::PlayerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

//void PlayerController::SetState(int state)
//{
//	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
//	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
//	switch (state)
//	{
//	case JUMP:
//		if((m_state & JUMP) != JUMP){
//			rigidbody->SetVelocity(Vector2(0, -.1));
//			m_state &= ~State::IDLE;
//			m_state |= State::JUMP;
//		}
//		break; 
//	case ~JUMP:
//		rigidbody->SetVelocity(Vector2(NULL, 0));
//		break;
//	case MOVE_RIGHT:
//		rigidbody->SetVelocity(.1, NULL);
//
//		m_state &= ~State::MOVE_LEFT;
//		m_state |= State::MOVE_RIGHT;
//		break;
//	case ~MOVE_RIGHT:
//		rigidbody->SetVelocity(0);
//		m_state &= ~State::MOVE_RIGHT;
//		break;
//	case MOVE_LEFT:
//		rigidbody->SetVelocity(-.1);
//
//		m_state &= ~State::MOVE_RIGHT;
//		m_state |= State::MOVE_LEFT;
//		break;
//	case ~MOVE_LEFT:
//		rigidbody->SetVelocity(0);
//		m_state &= ~State::MOVE_LEFT;
//		break;
//	case MOVE_DOWN:
//		rigidbody->SetVelocity(NULL,.1);
//		break;
//	case ~MOVE_DOWN:
//		rigidbody->SetVelocity(NULL, 0);
//		break;
//	case IDLE:
//		if((m_state & MOVE_RIGHT) == MOVE_RIGHT){}
//		else if((m_state & MOVE_LEFT) == MOVE_LEFT)
//		rigidbody->SetVelocity(Vector2(0, 0));
//
//		m_state &= ~State::JUMP;
//		m_state &= ~State::MOVE_LEFT;
//		m_state &= ~State::MOVE_RIGHT;
//		m_state |= State::IDLE;
//		break;
//	}
//
//	//CDebug::Log("Current State: %d\n", m_state);
//}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	//CDebug::Log("Collision ground \n");
}

void PlayerController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	Vector2 velocity = rigidbody->GetVelocity();

	if(velocity.y > 0)
	{
		anim->SetBool(L"isFall", true);
		anim->SetBool(L"isLandFall", false);
	}
	else
	{
		if (velocity.y == 0 && anim->GetBool(L"isFall")) {
			anim->SetBool(L"isLandFall", true);
			anim->SetBool(L"isFall", false);
		}
		else {
			anim->SetBool(L"isFall", false);
			anim->SetBool(L"isLandFall", false);
		}
	}

	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_SPACE)) {
		anim->SetBool(L"isShoot", true);
	}
	if (input->KeyUp(DIK_SPACE)) {
		anim->SetBool(L"isShoot", false);
	}

	if (input->KeyDown(DIK_UPARROW)) {
		if (!anim->GetBool(L"isJump")) {
			anim->SetBool(L"isJump", true);
			rigidbody->AddVelocity(Vector2(0, -.3));
		}
	}
	if (input->KeyUp(DIK_UPARROW)) {
		anim->SetBool(L"isJump", false);
	}

	if (anim->GetBool(L"isDash") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		anim->SetBool(L"isDash", false);
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool(L"isDash")) {
			const bool isLeft = renderer->GetFlipX();
			rigidbody->AddVelocity(Vector2(isLeft ? -0.2 : 0.2, 0));
			anim->SetBool(L"isDash", true);
		}
	}
	if (input->KeyUp(DIK_Z)) {
	}

	if (input->KeyDown(DIK_LEFTARROW)) {
		renderer->SetFlipX(true);
		anim->SetBool(L"isRun", true);
		rigidbody->AddVelocity(Vector2(-.1, 0));
	}
	if (input->KeyUp(DIK_LEFTARROW)) {
		if (anim->GetBool(L"isRun")) {
			anim->SetBool(L"isRun", false);
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

	if (input->KeyDown(DIK_RIGHTARROW)) {
		renderer->SetFlipX(false);
		anim->SetBool(L"isRun", true);
		rigidbody->AddVelocity(Vector2(.1, 0));
	}
	if (input->KeyUp(DIK_RIGHTARROW)) {
		if (anim->GetBool(L"isRun")) {
			anim->SetBool(L"isRun", false);
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

	if(input->KeyDown(DIK_DOWNARROW))
	{
		//SetState(MOVE_DOWN);
	}
	if (input->KeyUp(DIK_DOWNARROW))
	{
		//SetState(~MOVE_DOWN);
	}

	if (rigidbody->GetVelocity() == Vector2(0, 0) && m_state != IDLE)
	{
		//SetState(IDLE);
	}
}

void PlayerController::Render()
{
}
