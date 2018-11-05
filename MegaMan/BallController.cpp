#include "BallController.h"
#include "../Framework/Renderer.h"
#include "../Framework/GameObject.h"
<<<<<<< HEAD:MegaMan/BallController.cpp
#include "../Framework/Transform.h"
#include "../Framework/Rigidbody.h"
#include "../Framework/Input.h"
=======
>>>>>>> origin/dev:MegaMan/MarioController.cpp

using namespace Megaman;

<<<<<<< HEAD:MegaMan/BallController.cpp
BallController::BallController(CGameObject* game_object) : CMonoBehavior(game_object)
=======
MarioController::MarioController(Framework::CGameObject* game_object) : CComponent(game_object)
>>>>>>> origin/dev:MegaMan/MarioController.cpp
{
	width = _gameObject->GetComponent<Framework::CRenderer>()->GetWidth();
	height = _gameObject->GetComponent<Framework::CRenderer>()->GetHeight();
	pos = _gameObject->GetComponent<Framework::CTransform>()->Get_Position();
}

void BallController::Update(DWORD dt)
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
		//rigidbody->SetVelocity(Vector2(.1, 0));
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

void BallController::Render()
{

}

void BallController::OnCollisionEnter(CCollision* collision)
{
	OutputDebugString(collision->GetCollider()->GetGameObject()->GetName());
}
