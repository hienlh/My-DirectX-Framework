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

void BallController::OnCollisionEnter(CCollision* collision)
{
	//CDebug::Log("Collision ground \n");
}

void BallController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	const Vector2 velocity = rigidbody->GetVelocity();

	if (velocity.y > 0)
	{
		anim->SetBool(L"isFall", true);
		anim->SetBool(L"isLandfall", false);
		anim->SetBool(L"isJump", true);
	}
	else if (velocity.y == 0) {
		if (anim->GetBool(L"isFall")) anim->SetBool(L"isLandfall", true);
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
			rigidbody->AddVelocity(Vector2(0, -.3));
		}
	}
	if (input->KeyUp(DIK_UPARROW)) {
	}

	if (anim->GetBool(L"isDash") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		if (!anim->GetBool(L"isRun"))
		{
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
		else
		{
			const bool isLeft = renderer->GetFlipX();
			rigidbody->SetVelocity(Vector2(isLeft ? -.2 : .2, MAX_VELOCITY));
		}
		anim->SetBool(L"isDash", false);
	}

	if (anim->GetBool(L"isDash") && !anim->GetCurrentAnimation()->IsLastFrame())
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? -0.2 : 0.2, MAX_VELOCITY));
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool(L"isDash")) {
			anim->SetBool(L"isDash", true);
		}
	}
	if (input->KeyUp(DIK_Z)) {
	}

	if (input->KeyDown(DIK_W)) {
		anim->SetBool(L"isClimbLadder", true);
		rigidbody->SetVelocity(MAX_VELOCITY, -0.1);
		rigidbody->SetGravityScale(0);
	}
	if (input->KeyUp(DIK_W)) {
		anim->SetBool(L"isClimbLadder", false);
		rigidbody->SetVelocity(MAX_VELOCITY, 0);
		rigidbody->SetGravityScale(1);
	}

	if (input->KeyDown(DIK_Q)) {
		anim->SetBool(L"isClinging", true);
	}
	if (input->KeyUp(DIK_Q)) {

	}
	if (anim->GetBool(L"isLandfall") || anim->GetBool(L"isJump"))
	{
		anim->SetBool(L"isClinging", false);
	}
	if (anim->GetBool(L"isClinging") && anim->GetBool(L"isJump"))
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? .3 / 4 : -.3 / 4, -.3 / 2));
		anim->SetBool(L"isClinging", false);
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

	if (m_isCollideLadder == true && anim->GetBool(L"isClimbLadder"))
	{
		rigidbody->SetVelocity(0, MAX_VELOCITY);
	}
}

void BallController::Render()
{
}
