#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"

using namespace Framework;

CCollision::CCollision(const CCollision& collision, bool swap)
{
	if (!swap) {
		m_pCollider = collision.m_pCollider;
		m_pOtherCollider = collision.m_pOtherCollider;
	}
	else
	{
		m_pCollider = collision.m_pOtherCollider;
		m_pOtherCollider = collision.m_pCollider;
	}
}

CCollision::CCollision(CGameObject* collider, CGameObject* otherCollider)
{
	m_pCollider = collider;
	m_pOtherCollider = otherCollider;
}

CCollision::~CCollision()
{
	SAFE_DELETE(m_pCollider);
	SAFE_DELETE(m_pOtherCollider);
}

std::string CCollision::GetOtherColliderName(std::string name) const
{
	const std::string colliderName = m_pCollider->GetName();
	const std::string otherColliderName = m_pOtherCollider->GetName();

	if (otherColliderName == name) return colliderName;
	if (colliderName == name) return otherColliderName;
	return "";
}

bool CCollision::CheckNameInCollision(std::string colliderName) const
{
	return m_pCollider->GetName() == colliderName || 
		m_pOtherCollider->GetName() == colliderName;
}

bool CCollision::CollisionBetween(std::string name, std::string otherName) const
{
	const std::string colliderName = m_pCollider->GetName();
	const std::string otherColliderName = m_pOtherCollider->GetName();
	return (colliderName == name && otherColliderName == otherName) || (colliderName == otherName && otherColliderName == name);
}

CCollision* CCollision::Swap()
{
	const auto tmp = m_pCollider;
	m_pCollider = m_pOtherCollider;
	m_pOtherCollider = tmp;
	return this;
}

