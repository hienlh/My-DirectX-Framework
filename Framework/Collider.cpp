#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

using namespace Framework;

CCollider::CCollider(const CCollider& collider) : CComponent(collider)
{
	m_Anchor = collider.m_Anchor;
	m_AutoBoundSize = collider.m_AutoBoundSize;
	m_Bound = collider.m_Bound;
	m_IsDebugging = collider.m_IsDebugging;
	m_IsTrigger = collider.m_IsTrigger;
	m_Offset = collider.m_Offset;
	m_UsedByEffector = collider.m_UsedByEffector;
	m_Name = collider.m_Name;
}

CCollider::CCollider(CGameObject* gameObject) : CComponent(gameObject)
{
	m_Offset = VECTOR2_ZERO;
	m_IsTrigger = false;
	m_Bound = Bound();
	m_UsedByEffector = true;
	m_IsDebugging = false;
	m_AutoBoundSize = false;
	m_Anchor = { 0.5, 0.5 };
}


/**
 * \brief Main function to calculate the bound for handling collision
 * \return The global bound
 */
Bound CCollider::GetBoundGlobal() const
{
	const auto transform = m_pGameObject->GetComponent<CTransform>();
	const Vector2 pos = transform->Get_Position();
	const Vector2 scale = transform->Get_Scale();
	const Vector2 size = Vector2(m_Bound.Size().x * scale.x, m_Bound.Size().y * scale.y);
	const Vector2 topLeft = Vector2(pos.x - m_Anchor.x * size.x, pos.y - m_Anchor.y * size.y);
	return Bound(topLeft + m_Offset, size);
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

Vector2 CCollider::GetAnchor() const
{
	return m_Anchor;
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
	if (m_pGameObject->GetComponent<CRigidbody>()->GetIsKinematic() && autoBoundSize) return;
	
	m_AutoBoundSize = autoBoundSize;
}

void CCollider::SetAnchor(Vector2 anchor)
{
	m_Anchor = anchor;
	m_pGameObject->GetScene()->AddColliderObject(m_pGameObject, true);
}
