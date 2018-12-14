#include "CameraController.h"
#include "../Framework/GameObject.h"

CameraController::CameraController(Framework::CGameObject* game_object) : CMonoBehavior(game_object)
{
}

void CameraController::Update(DWORD dt)
{
	if(isFollow)
		Following();
	//_gameObject->GetComponent<CTransform>()->Set_Position(_gameObject->GetComponent<CTransform>()->Get_Position() + Vector2(1, 1));
}

void CameraController::Render()
{

}

CameraController* CameraController::Clone() const
{
	return new CameraController(*this);
}

void CameraController::Following()
{
	if(m_target)
	{
		m_pGameObject->GetComponent<Framework::CTransform>()->Set_Position(m_target->GetComponent<Framework::CTransform>()->Get_Position());
	}
}
