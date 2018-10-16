#include "MarioController.h"
#include "../Framework/Renderer.h"
#include "../Framework/GameObject.h"
#include "../Framework/Transform.h"

using namespace Framework;

void MarioController::Update(DWORD dt)
{
	Vector2 pos = _gameObject->GetComponent<CTransform>()->Get_Position();
	pos += Vector2(0, 1) * dt / 10;
	_gameObject->GetComponent<CTransform>()->Set_Position(pos);
}

void MarioController::Render()
{
}
