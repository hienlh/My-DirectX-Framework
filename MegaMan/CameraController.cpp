#include "CameraController.h"
#include "../Framework/GameObject.h"

using namespace Megaman;

<<<<<<< HEAD
CameraController::CameraController(CGameObject* game_object) : CMonoBehavior(game_object)
=======
CameraController::CameraController(Framework::CGameObject* game_object) : CComponent(game_object)
>>>>>>> origin/dev
{
}

void CameraController::Update(DWORD dt)
{
	Following();
	//_gameObject->GetComponent<CTransform>()->Set_Position(_gameObject->GetComponent<CTransform>()->Get_Position() + Vector2(1, 1));
}

void CameraController::Render()
{

}

void CameraController::Following()
{
	if(m_target)
	{
		_gameObject->GetComponent<Framework::CTransform>()->Set_Position(m_target->GetComponent<Framework::CTransform>()->Get_Position());
	}
}
