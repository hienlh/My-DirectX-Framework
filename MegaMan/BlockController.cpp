#include "BlockController.h"
#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Input.h"

using namespace Megaman;

BlockController::BlockController(Framework::CGameObject* game_object) : CComponent(game_object)
{
	m_isGoDown = true; 
	m_isRight = false;
	m_pos = _gameObject->GetComponent<Framework::CTransform>()->Get_Position();
	m_size = _gameObject->GetComponent<Framework::CRenderer>()->GetSize();
}

void BlockController::Update(DWORD dt)
{
	m_pos = _gameObject->GetComponent<Framework::CTransform>()->Get_Position();
	auto transform = _gameObject->GetComponent<Framework::CTransform>();
	if (m_pos.y + m_size.y >= SCREEN_HEIGHT) {
		transform->Set_Position(Vector2(transform->Get_Position().x, SCREEN_HEIGHT - m_size.y));
		SetIsGoDown(false);
	}
	else if (m_pos.y <= 0)
	{
		transform->Set_Position(Vector2(transform->Get_Position().x, 0));
		SetIsGoDown(true);
	}

	Move();
}

void BlockController::Render()
{
}

void BlockController::Move()
{
	auto rigidbody = _gameObject->GetComponent<CRigidbody>();
	auto input = Framework::CInput::GetInstance();
	for (unsigned short x = 0; x <= 256; x++)
	{
		if (input->KeyDown(x))
		{
			if (x == 65 && !m_isRight)
				rigidbody->SetVelocity(Vector2(0, 3) * (m_isGoDown ? 1 : -1));

			if (x == 1 && m_isRight)
				rigidbody->SetVelocity(Vector2(0, 3) *(m_isGoDown ? 1 : -1));
		}
		if (input->KeyUp(x))
		{
			if (x == 65 && !m_isRight)
				rigidbody->SetVelocity(Vector2(0, 0));

			if (x == 1 && m_isRight)
				rigidbody->SetVelocity(Vector2(0, 0));
		}
	}
}