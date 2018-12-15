#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"

using namespace Framework;

CCollision::CCollision(CCollider* collider, CCollider* otherCollider)
{
	m_pCollider = collider;
	m_pOtherCollider = otherCollider;
}

CCollision::CCollision(CGameObject* collider, CGameObject* otherCollider)
{
	m_pCollider = collider->GetComponent<CCollider>();
	m_pOtherCollider = otherCollider->GetComponent<CCollider>();
}

CCollision::~CCollision()
{
	SAFE_DELETE(m_pCollider);
	SAFE_DELETE(m_pOtherCollider);
}

bool CCollision::CollisionBetween(std::string name, std::string otherName) const
{
	std::string colliderName = m_pCollider->GetGameObject()->GetName();
	std::string otherColliderName = m_pOtherCollider->GetGameObject()->GetName();
	return (colliderName == name && otherColliderName == otherName) || (colliderName == otherName && otherColliderName == name);
}

