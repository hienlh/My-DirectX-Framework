#include "MarioController.h"
#include "../Framework/Renderer.h"
#include "../Framework/GameObject.h"

using namespace Megaman;

MarioController::MarioController(Framework::CGameObject* game_object) : CComponent(game_object)
{
	width = _gameObject->GetComponent<Framework::CRenderer>()->GetWidth();
	height = _gameObject->GetComponent<Framework::CRenderer>()->GetHeight();
	pos = _gameObject->GetComponent<Framework::CTransform>()->Get_Position();
}

void MarioController::Update(DWORD dt)
{
	pos = _gameObject->GetComponent<Framework::CTransform>()->Get_Position();
	if (pos.y + height >= SCREEN_HEIGHT) 
		_gameObject->GetComponent<Framework::CTransform>()->Set_Position(Vector2(pos.x, SCREEN_HEIGHT - height));

	auto rigidbody = _gameObject->GetComponent<CRigidbody>();
	auto transform = _gameObject->GetComponent<Framework::CTransform>();
	
	Vector2 leftPos = leftBlock->GetComponent<Framework::CTransform>()->Get_Position();
	Vector2 leftSize = leftBlock->GetComponent<Framework::CRenderer>()->GetSize();
	Vector2 rightPos = rightBlock->GetComponent<Framework::CTransform>()->Get_Position();
	Vector2 rightSize = rightBlock->GetComponent<Framework::CRenderer>()->GetSize();

	//va cham voi block trai
	if (pos.x <= pos.x + leftSize.x && (pos.y + height >= leftPos.y && pos.y <= leftPos.y + leftSize.y))
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi block phai
	if (pos.x + width >= rightPos.x && (pos.y + height >= rightPos.y && pos.y <= rightPos.y + rightSize.y))
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(-velocity.x, velocity.y));
	}

	//va cham voi thanh duoi
	if (pos.y + height >= 480)
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(velocity.x, -velocity.y));
	}

	//va cham voi thanh tren
	if (pos.y <= 0)
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(velocity.x, -velocity.y));
	}

	//Out screen
	if (pos.x + width <= 0 || pos.x >= SCREEN_WIDTH)
	{
		transform->Set_Position(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	}
}

void MarioController::Render()
{

}
