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
	SAFE_FREE(m_pCollider);
	SAFE_FREE(m_pOtherCollider);
}

Vector2 CCollision::GetRelativeVelocity()
{
	return Vector2();
}

