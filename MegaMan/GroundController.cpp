#include "GroundController.h"
#include "Input.h"
#include "Rigidbody.h"
#include "GameObject.h"

void GroundController::OnCollisionEnter(Framework::CCollision* collision)
{
}

void GroundController::Update(const DWORD &dt)
{
	Framework::CRigidbody *rigidbody = m_pGameObject->GetComponent<Framework::CRigidbody>();
	Framework::CInput *input = Framework::CInput::GetInstance();
}

void GroundController::Render()
{
}
