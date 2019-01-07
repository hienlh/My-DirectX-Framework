#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"

using namespace Framework;

CCollision::CCollision(const CCollision& collision, const bool &swap)
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

const bool& CCollision::CheckNameInCollision(const std::string& colliderName) const
{
	return m_pCollider->GetName() == colliderName || 
		m_pOtherCollider->GetName() == colliderName;
}

const bool& CCollision::CollisionBetween(const std::string& name, const std::string& otherName) const
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

