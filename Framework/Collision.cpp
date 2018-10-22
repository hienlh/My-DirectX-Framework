#include "Collision.h"
#include "GameObject.h"

using namespace Framework;

CCollision::CCollision(CCollider* collider, CCollider* otherCollider)
{
	m_collider = collider;
	m_otherCollider = otherCollider;
}

CCollision::CCollision(CGameObject* collider, CGameObject* otherCollider)
{
	m_collider = collider->GetComponent<CCollider>();
	m_otherCollider = otherCollider->GetComponent<CCollider>();
}

CCollision::~CCollision()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_otherCollider);
}

Vector2 CCollision::GetRelativeVelocity()
{
	return Vector2();
}
