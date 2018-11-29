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
	m_IsDebugging = false;
	m_AutoBoundSize = false;
}

Bound CCollider::GetBoundGlobal() const
{
	Vector2 pos = m_pGameObject->GetComponent<CTransform>()->Get_Position();
	Vector2 scale = m_pGameObject->GetComponent<CTransform>()->Get_Scale();
	Vector2 size = Vector2(m_Bound.Size().x * scale.x, m_Bound.Size().y * scale.y);
	return Bound(pos + m_Offset, size);
}

bool CCollider::GetUsedByEffector() const
{
	return m_UsedByEffector;
}

bool CCollider::GetIsDebugging() const
{
	return m_IsDebugging;
}

bool CCollider::GetAutoBoundSize() const
{
	return m_AutoBoundSize;
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

void CCollider::SetIsDebugging(bool isDebugging)
{
	m_IsDebugging = isDebugging;
}

void CCollider::SetAutoBoundSize(bool autoBoundSize)
{
	m_AutoBoundSize = autoBoundSize;
}
