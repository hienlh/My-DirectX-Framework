#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

using namespace Framework;

CCollider::CCollider(CGameObject* gameObject) : CComponent(gameObject)
{
	m_Offset = VECTOR2_ZERO;
	m_IsTrigger = false;
	m_Bound = Bound();
	m_UsedByEffector = true;
}

Bound CCollider::GetBoundGlobal() const
{
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	return Bound(pos + m_Offset, m_Bound.Size());
}

bool CCollider::GetUsedByEffector() const
{
	return m_UsedByEffector;
}

void CCollider::SetUsedByEffector(bool usedByEffector)
{
	m_UsedByEffector = usedByEffector;
}

//void CCollider::SetBoundSize(Vector2 size)
//{
//	m_Bound = Bound(Vector2(0, 0), size);
//}

void CCollider::SetOffset(Vector2 offset)
{
	m_Offset = offset;
}
