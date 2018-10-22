#include "Collider.h"
#include "GameObject.h"

CCollider::CCollider(CGameObject* gameObject) : CComponent(gameObject)
{
	m_Offset = Vector2(0, 0);
	m_IsTrigger = false;
	m_Bound = Bounds();
	m_UsedByEffector = true;
}

Bounds CCollider::GetBoundGlobal() const
{
	Vector2 pos = _gameObject->GetComponent<CTransform>()->Get_Position();
	return Bounds(pos + m_Offset, m_Bound.Size());
}

bool CCollider::GetUsedByEffector() const
{
	return m_UsedByEffector;
}

void CCollider::SetUsedByEffector(bool usedByEffector)
{
	m_UsedByEffector = usedByEffector;
}

void CCollider::SetBoundSize(Vector2 size)
{
	m_Bound = Bounds(Vector2(0, 0), size);
}

void CCollider::SetOffet(Vector2 offset)
{
	m_Offset = offset;
}
