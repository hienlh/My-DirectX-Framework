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
	// CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	// CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	// switch (state)
	// {
	// case JUMP:
	// 	if((m_state & JUMP) != JUMP){
	// 		rigidbody->SetVelocity(Vector2(0, -.1));
	// 		m_state &= ~State::IDLE;
	// 		m_state |= State::JUMP;
	// 	}
	// 	break; 
	// case ~JUMP:
	// 	rigidbody->SetVelocity(Vector2(NULL, 0));
	// 	break;
	// case MOVE_RIGHT:
	// 	rigidbody->SetVelocity(.1, NULL);
	//
	// 	m_state &= ~State::MOVE_LEFT;
	// 	m_state |= State::MOVE_RIGHT;
	// 	break;
	// case ~MOVE_RIGHT:
	// 	rigidbody->SetVelocity(0);
	// 	m_state &= ~State::MOVE_RIGHT;
	// 	break;
	// case MOVE_LEFT:
	// 	rigidbody->SetVelocity(-.1);
	//
	// 	m_state &= ~State::MOVE_RIGHT;
	// 	m_state |= State::MOVE_LEFT;
	// 	break;
	// case ~MOVE_LEFT:
	// 	rigidbody->SetVelocity(0);
	// 	m_state &= ~State::MOVE_LEFT;
	// 	break;
	// case MOVE_DOWN:
	// 	rigidbody->SetVelocity(NULL,.1);
	// 	break;
	// case ~MOVE_DOWN:
	// 	rigidbody->SetVelocity(NULL, 0);
	// 	break;
	// case IDLE:
	// 	if((m_state & MOVE_RIGHT) == MOVE_RIGHT){}
	// 	else if((m_state & MOVE_LEFT) == MOVE_LEFT)
	// 	rigidbody->SetVelocity(Vector2(0, 0));
	//
	// 	m_state &= ~State::JUMP;
	// 	m_state &= ~State::MOVE_LEFT;
	// 	m_state &= ~State::MOVE_RIGHT;
	// 	m_state |= State::IDLE;
	// 	break;
	// }

	//CDebug::Log("Current State: %d\n", m_state);
}

void BallController::OnCollisionEnter(CCollision* collision)
{
	/*CDebug::Log(collision->GetCollider()->GetName());
	CDebug::Log(collision->GetOtherCollider()->GetName());
	CDebug::Log("\n");*/
	if (collision->GetCollider()->GetName() == L"Wall" || collision->GetOtherCollider()->GetName() == L"Wall") {
		m_isCollideWall = true;
		CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
		anim->SetBool(L"isJump", false);
		anim->SetBool(L"isClinging", true);
		CDebug::Log("Cham tuong");
	}
	else {
		m_isCollideWall = false;
	}
}

void BallController::OnCollisionStay(CCollision* collision)
{
	
}


void BallController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	Vector2 velocity = rigidbody->GetVelocity();

	if(velocity.y > 0)
	{
		anim->SetBool(L"isFall", true);
		anim->SetBool(L"isLandfall", false);
		anim->SetBool(L"isJump", true);
	}
	else if (velocity.y == 0 ) {
		if(anim->GetBool(L"isFall")) anim->SetBool(L"isLandfall", true);
		anim->SetBool(L"isFall", false);
		anim->SetBool(L"isJump", false);
	}
	else {
		anim->SetBool(L"isFall", false);
		anim->SetBool(L"isLandfall", false);
	}

	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_SPACE)) {
		anim->SetBool(L"isShoot", true);
	}
	if (input->KeyUp(DIK_SPACE)) {
		anim->SetBool(L"isShoot", false);
	}

	if (input->KeyDown(DIK_E)) {
		anim->SetBool(L"isPowering", true);
	}
	if (input->KeyUp(DIK_E)) {
		anim->SetBool(L"isPowering", false);
	}

	if (input->KeyDown(DIK_UPARROW)) {
		if (!anim->GetBool(L"isJump")) {
			anim->SetBool(L"isJump", true);
			rigidbody->AddVelocity(Vector2(0, -MEGAMAN_JUMPFORCE));
		}
	}
	if (input->KeyUp(DIK_UPARROW)) {
		
	}

	if (anim->GetBool(L"isDash") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		if (!anim->GetBool(L"isRun"))
		{
			rigidbody->SetVelocity(Vector2(0, 0));
		}
		else
		{
			const bool isLeft = renderer->GetFlipX();
			rigidbody->SetVelocity(Vector2(isLeft ? -MEGAMAN_VELOCITY : MEGAMAN_VELOCITY, 0));
		}
		anim->SetBool(L"isDash", false);
		// anim->SetBool(L"isShoot", false);
	}

	if (anim->GetBool(L"isDash") && !anim->GetCurrentAnimation()->IsLastFrame())
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? -MEGAMAN_DASH : MEGAMAN_DASH, 0));
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool(L"isDash")) {
			const bool isLeft = renderer->GetFlipX();
			// rigidbody->AddVelocity(Vector2(isLeft ? -0.2 : 0.2, 0));
			anim->SetBool(L"isDash", true);
		}
	}
	if (input->KeyUp(DIK_Z)) {
		// anim->SetBool(L"isDash", false);
	}

	if (input->KeyDown(DIK_W)) {
		anim->SetBool(L"isClimbLadder", true);
	}
	if (input->KeyUp(DIK_W)) {
		anim->SetBool(L"isClimbLadder", false);
	}
	
	if (input->KeyDown(DIK_Q)) {
		anim->SetBool(L"isClinging", true);
	}
	if (input->KeyUp(DIK_Q)) {
		
	}
	if(anim->GetBool(L"isLandfall") || anim->GetBool(L"isJump"))
	{
		anim->SetBool(L"isClinging", false);
	}
	if(anim->GetBool(L"isClinging") && anim->GetBool(L"isJump"))
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? MEGAMAN_JUMPFORCE/4 : -MEGAMAN_JUMPFORCE/4, -MEGAMAN_JUMPFORCE/2));
		anim->SetBool(L"isClinging", false);
	}

	if (input->KeyDown(DIK_LEFTARROW)) {
		renderer->SetFlipX(true);
		anim->SetBool(L"isRun", true);
		rigidbody->SetVelocity(Vector2(-MEGAMAN_VELOCITY,0));
	}
	if (input->KeyUp(DIK_LEFTARROW)) {
		anim->SetBool(L"isRun", false);
		rigidbody->SetVelocity(Vector2(0,0));
	}

	if (input->KeyDown(DIK_RIGHTARROW)) {
		renderer->SetFlipX(false);
		anim->SetBool(L"isRun", true);
		rigidbody->SetVelocity(Vector2(MEGAMAN_VELOCITY, 0));

	}
	if (input->KeyUp(DIK_RIGHTARROW)) {
		anim->SetBool(L"isRun", false);
		rigidbody->SetVelocity(Vector2(0, 0));
	}

	if(input->KeyDown(DIK_DOWNARROW))
	{
		SetState(MOVE_DOWN);
	}
	if (input->KeyUp(DIK_DOWNARROW))
	{
		SetState(~MOVE_DOWN);
	}
	if(m_isCollideLadder==true && anim->GetBool(L"isClimbLadder"))
	{
		Vector2 currentVeclocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(0,currentVeclocity.y);
	}

	if (rigidbody->GetVelocity() == Vector2(0, 0) && m_state != IDLE)
	{
		SetState(IDLE);
	}

}

void BallController::Render()
{
}
