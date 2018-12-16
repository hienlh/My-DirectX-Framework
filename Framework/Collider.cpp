#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

using namespace Framework;

CCollider::CCollider(const CCollider& collider) : CComponent(collider)
{
	m_Anchor = collider.m_Anchor;
	m_AutoBoundSize = collider.m_AutoBoundSize;
	m_Bound = collider.m_Bound;
	m_IsTrigger = collider.m_IsTrigger;
	m_Offset = collider.m_Offset;
	m_UsedByEffector = collider.m_UsedByEffector;
	m_Name = collider.m_Name;
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

/**
 * \brief Get area used in QuadTree
 * \return 
 */
Rect CCollider::GetBoundArea() const
{
	const auto limitedArea = m_pGameObject->GetComponent<CRigidbody>()->GetLimitedArea();
	const auto boundSize = m_Bound.Size();

	const float left = limitedArea.left - boundSize.x * m_Anchor.x;
	const float right = limitedArea.right + boundSize.x * (1 - m_Anchor.x);
	const float top = limitedArea.top - boundSize.y * m_Anchor.y;
	const float bottom = limitedArea.bottom + boundSize.y * (1 - m_Anchor.y);

	return Rect(top, left, bottom, right);
}

bool CCollider::GetUsedByEffector() const
{
	return m_UsedByEffector;
}

bool CCollider::GetAutoBoundSize() const
{
	return m_AutoBoundSize;
}

bool CCollider::GetIsTrigger() const
{
	return m_IsTrigger;
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

void CCollider::SetAutoBoundSize(bool autoBoundSize)
{
	if (m_pGameObject->GetComponent<CRigidbody>()->GetIsKinematic() && autoBoundSize) return;
	
	m_AutoBoundSize = autoBoundSize;
}

void CCollider::SetAnchor(Vector2 anchor)
{
	m_Anchor = anchor;
	m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
}

void CCollider::SetIsTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}
