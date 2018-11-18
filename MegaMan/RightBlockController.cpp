#include "RightBlockController.h"
#include "Rigidbody.h"
#include "CameraController.h"
#include "Input.h"
#include "BoxCollider.h"

RightBlockController::RightBlockController(CGameObject* game_object) : CMonoBehavior(game_object)
{
}

void RightBlockController::OnCollisionEnter(CCollision* collision)
{
	m_pGameObject->GetComponent<CRigidbody>()->SetVelocity(Vector2(0, .1));
}

void RightBlockController::Update(DWORD dt)
{
	CRigidbody *rigidbody = m_pGameObject->GetComponent<CRigidbody>();
	CInput *input = CInput::GetInstance();

	if (input->ButtonDown(0))
		rigidbody->SetVelocity(Vector2(0, .1));
	if (input->ButtonUp(0))
		rigidbody->SetVelocity(Vector2(0, 0));
	if (input->ButtonDown(1))
		rigidbody->SetVelocity(Vector2(0, -.1));
	if (input->ButtonUp(1))
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

void RightBlockController::Render()
{
}