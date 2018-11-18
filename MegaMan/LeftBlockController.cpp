#include "LeftBlockController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "BoxCollider.h"
#include "RightBlockController.h"

LeftBlockController::LeftBlockController(CGameObject* game_object) : CMonoBehavior(game_object)
{
}

void LeftBlockController::OnCollisionEnter(CCollision* collision)
{
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(Vector2(0, .1));
}

void LeftBlockController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CInput *input = CInput::GetInstance();

	if (input->KeyDown(31))
		rigidbody->SetVelocity(Vector2(0, .1));
	if (input->KeyUp(31))
		rigidbody->SetVelocity(Vector2(0, 0));
	if (input->KeyDown(17))
		rigidbody->SetVelocity(Vector2(0, -.1));
	if (input->KeyUp(17))
		rigidbody->SetVelocity(Vector2(0, 0));

	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	CTransform *transform = m_pGameObject->GetComponent<CTransform>();
	Vector2 size = m_pGameObject->GetComponent<CBoxCollider>()->GetSize();

	if (pos.y + size.y >= SCREEN_HEIGHT)
	{
		transform->Set_Position(Vector2(transform->Get_Position().x, SCREEN_HEIGHT - size.y));
	}
	else if (pos.y <= 0)
	{
		transform->Set_Position(Vector2(transform->Get_Position().x, 0));
	}
}

void LeftBlockController::Render()
{
}