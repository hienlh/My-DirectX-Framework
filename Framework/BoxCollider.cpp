#include "BoxCollider.h"
#include "GameObject.h"

using namespace Framework;

CBoxCollider::CBoxCollider(CGameObject* gameObject) : CCollider(gameObject)
{
	const auto transform = _gameObject->GetComponent<CTransform>();
	_size = Vector2(1, 1);
	if(const auto renderer = _gameObject->GetComponent<CRenderer>())
	{
		_size = renderer->GetSize();
	}
	m_offset = Vector2(0, 0);
	const Vector2 topLeft = transform->Get_Position() + m_offset;
	m_bounds = Bounds(topLeft, _size);
}

void CBoxCollider::Update(DWORD dt)
{
	m_bounds = Bounds(_gameObject->GetComponent<CTransform>()->Get_Position() + m_offset, _size);
}

void CBoxCollider::Render()
{
}
