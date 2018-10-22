#include "Collider.h"
#include "GameObject.h"

CCollider::CCollider(CGameObject* gameObject) : CComponent(gameObject)
{
	m_offset = Vector2(0, 0);
	m_isTrigger = false;
	m_bounds = Bounds();
	m_usedByEffector = true;
}

Bounds CCollider::GetBounds() const
{
	return m_bounds;
}

bool CCollider::GetUsedByEffector() const
{
	return m_usedByEffector;
}
