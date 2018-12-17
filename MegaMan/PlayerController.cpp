#include "PlayerController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Graphic.h"
#include "Input.h"
#include "Animator.h"

PlayerController::PlayerController(const PlayerController& PC) : CMonoBehavior(PC)
{
	m_speed = PC.m_speed;
}

PlayerController* PlayerController::Clone() const
{
	return new PlayerController(*this);
}

PlayerController::PlayerController(CGameObject* gameObject) : CMonoBehavior(gameObject)
{

}

void PlayerController::OnCollisionEnter(CCollision* collision)
{
	auto anim = m_pGameObject->GetComponent<CAnimator>();

	CDebug::Log("%s - %s\n", collision->GetCollider()->GetName().c_str(),
	            collision->GetOtherCollider()->GetName().c_str());
	if(strstr(collision->GetOtherCollider()->GetName().c_str(), std::string("Wall").c_str()))
	{
		anim->SetBool("isClinging", true);
		anim->SetBool("isJump", false);
	}
	//m_pGameObject->GetComponent<CAnimator>()->SetBool("isJump", false);
}

void PlayerController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	CRenderer *renderer = m_pGameObject->GetComponent<CRenderer>();
	CAnimator *anim = m_pGameObject->GetComponent<CAnimator>();
	const Vector2 velocity = rigidbody->GetVelocity();

	if (velocity.y > 0)
	{
		anim->SetBool("isFall", true);
		anim->SetBool("isLandfall", false);
	}
	else if (velocity.y == 0) {
		if (anim->GetBool("isFall")) anim->SetBool("isLandfall", true);
		anim->SetBool("isClinging", false);
		anim->SetBool("isFall", false);
		anim->SetBool("isJump", false);
	}
	else {
		anim->SetBool("isFall", false);
		anim->SetBool("isLandfall", false);
	}

	CInput *input = CInput::GetInstance();

	if (input->KeyDown(DIK_SPACE)) {
		anim->SetBool("isShoot", true);
		Shoot();
	}
	if (input->KeyUp(DIK_SPACE)) {
		anim->SetBool("isShoot", false);
	}

	if (input->KeyDown(DIK_E)) {
		anim->SetBool("isPowering", true);
	}
	if (input->KeyUp(DIK_E)) {
		anim->SetBool("isPowering", false);
	}

	if (input->KeyDown(DIK_UPARROW)) {
		if (!anim->GetBool("isJump")) {
			anim->SetBool("isJump", true);
			rigidbody->AddVelocity(Vector2(0, -.3));
		}
	}
	if (input->KeyUp(DIK_UPARROW)) {
	}

	if (anim->GetBool("isDash") && anim->GetCurrentAnimation()->IsLastFrame())
	{
		if (!anim->GetBool("isRun"))
		{
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
		else
		{
			const bool isLeft = renderer->GetFlipX();
			rigidbody->SetVelocity(Vector2(isLeft ? -.2 : .2, MAX_VELOCITY));
		}
		anim->SetBool("isDash", false);
	}

	if (anim->GetBool("isDash") && !anim->GetCurrentAnimation()->IsLastFrame())
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? -0.2 : 0.2, MAX_VELOCITY));
	}

	if (input->KeyDown(DIK_Z)) {
		if (!anim->GetBool("isDash")) {
			anim->SetBool("isDash", true);
		}
	}
	if (input->KeyUp(DIK_Z)) {
	}

	if (input->KeyDown(DIK_W)) {
		anim->SetBool("isClimbLadder", true);
		rigidbody->SetVelocity(MAX_VELOCITY, -m_speed);
		rigidbody->SetGravityScale(0);
	}
	if (input->KeyUp(DIK_W)) {
		anim->SetBool("isClimbLadder", false);
		rigidbody->SetVelocity(MAX_VELOCITY, 0);
		rigidbody->SetGravityScale(1);
	}

	if (anim->GetBool("isLandfall") || anim->GetBool("isJump"))
	{
		anim->SetBool("isClinging", false);
	}

	if (anim->GetBool("isClinging") && anim->GetBool("isJump"))
	{
		const bool isLeft = renderer->GetFlipX();
		rigidbody->SetVelocity(Vector2(isLeft ? .3 / 4 : -.3 / 4, -.3 / 2));
		anim->SetBool("isClinging", false);
	}

	if (input->KeyDown(DIK_LEFTARROW)) {
		renderer->SetFlipX(true);
		anim->SetBool("isRun", true);
		rigidbody->AddVelocity(Vector2(-m_speed, 0));
	}
	if (input->KeyUp(DIK_LEFTARROW)) {
		if (anim->GetBool("isRun")) {
			anim->SetBool("isRun", false);
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

	if (input->KeyDown(DIK_RIGHTARROW)) {
		renderer->SetFlipX(false);
		anim->SetBool("isRun", true);
		rigidbody->AddVelocity(Vector2(m_speed, 0));
	}
	if (input->KeyUp(DIK_RIGHTARROW)) {
		if (anim->GetBool("isRun")) {
			anim->SetBool("isRun", false);
			rigidbody->SetVelocity(Vector2(0, MAX_VELOCITY));
		}
	}

	if (input->KeyDown(DIK_E)) {
		if(m_Power)
			m_Power->SetIsActive(true);
	}
	if (input->KeyUp(DIK_E)) {
		if (m_Power)
			m_Power->SetIsActive(false);
	}

	if(transform->Get_Position().x > 2320)
	{
		if (m_GenjiBos && !m_GenjiBos->GetIsActive())
			m_GenjiBos->SetIsActive(true);
	}
}

void PlayerController::Render()
{
}

void PlayerController::Shoot()
{
	const bool isLeft = m_pGameObject->GetComponent<CRenderer>()->GetFlipX();
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	pos.x += (isLeft ? -1 : 1) * 25;
	auto pBullet = CGameObject::Instantiate("BusterShot", nullptr, pos);
	pBullet->GetComponent<CRigidbody>()->SetVelocity({static_cast<float>((isLeft ? -1 : 1) * 0.3), 0 });
}
