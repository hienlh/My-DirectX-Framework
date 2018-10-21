#include "BlockController.h"
#include "../Framework/GameObject.h"
#include "../Framework/Input.h"

BlockController::BlockController(CGameObject* game_object) : CComponent(game_object)
{
	m_isGoDown = true; 
	m_isRight = false;
	m_pos = _gameObject->GetComponent<CTransform>()->Get_Position();
	m_size = _gameObject->GetComponent<CRenderer>()->GetSize();
}

void BlockController::Update(DWORD dt)
{
	m_pos = _gameObject->GetComponent<CTransform>()->Get_Position();
	auto transform = _gameObject->GetComponent<CTransform>();
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
	auto input = CInput::GetInstance();
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