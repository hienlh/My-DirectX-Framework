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
	m_Offset = Vector2(0, 0);
	m_Bound = Bounds(Vector2(0, 0), _size);
}

void CBoxCollider::Update(DWORD dt)
{
}

void CBoxCollider::Render()
{
}
