#include "MarioController.h"
#include "../Framework/Renderer.h"
#include "../Framework/GameObject.h"
#include "../Framework/Transform.h"
#include "../Framework/Rigidbody.h"
#include "../Framework/Input.h"

using namespace Framework;

MarioController::MarioController(CGameObject* game_object) : CMonoBehavior(game_object)
{
	width = _gameObject->GetComponent<CRenderer>()->GetWidth();
	height = _gameObject->GetComponent<CRenderer>()->GetHeight();
	pos = _gameObject->GetComponent<CTransform>()->Get_Position();
}

void MarioController::Update(DWORD dt)
{
	pos = _gameObject->GetComponent<CTransform>()->Get_Position();
	if (pos.y + height >= SCREEN_HEIGHT) 
		_gameObject->GetComponent<CTransform>()->Set_Position(Vector2(pos.x, SCREEN_HEIGHT - height));

	auto rigidbody = _gameObject->GetComponent<CRigidbody>();
	auto transform = _gameObject->GetComponent<CTransform>();
	
	Vector2 leftPos = leftBlock->GetComponent<CTransform>()->Get_Position();
	Vector2 leftSize = leftBlock->GetComponent<CRenderer>()->GetSize();
	Vector2 rightPos = rightBlock->GetComponent<CTransform>()->Get_Position();
	Vector2 rightSize = rightBlock->GetComponent<CRenderer>()->GetSize();

	//va cham voi thanh duoi
	if (pos.y + height >= 480)
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(velocity.x, -velocity.y));
	}

	//va cham voi thanh tren
	if (pos.y < 0)
	{
		auto velocity = rigidbody->GetVelocity();
		rigidbody->SetVelocity(Vector2(velocity.x, -velocity.y));
	}

	//Out screen
	if (pos.x + width <= 0 || pos.x >= SCREEN_WIDTH)
	{
		transform->Set_Position(Vector2(SCREEN_WIDTH / 2, rand() % 100 + 1));
		rigidbody->SetVelocity(Vector2(.1, 0));
	}

	/*auto input = CInput::GetInstance();
	for (unsigned short x = 0; x <= 256; x++)
	{
		if (input->KeyDown(x))
		{
			if (x == 66)
				rigidbody->SetVelocity(Vector2(0.1, 0));
		}
		if (input->KeyUp(x))
		{
			if (x == 66)
				rigidbody->SetVelocity(Vector2(0, 0));
		}
	}*/
}

void MarioController::Render()
{

}

void MarioController::OnCollisionEnter(CCollision* collision)
{
	OutputDebugString(collision->GetCollider()->GetGameObject()->GetName());
}
