#include "stdafx.h"
#include "Rigidbody.h"

#include "GameObject.h"

using namespace Framework;

CRigidbody::CRigidbody(const CRigidbody& rigidbody) : CComponent(rigidbody)
{
	m_gravityScale = rigidbody.m_gravityScale;
	m_isKinematic = rigidbody.m_isKinematic;
	m_mass = rigidbody.m_mass;
	m_velocity = rigidbody.m_velocity;
	m_Name = rigidbody.m_Name;
}

CRigidbody::CRigidbody(CGameObject * gameObject)
{
	this->m_pGameObject = gameObject;
	this->m_velocity = Vector2(0, 0);
	this->m_mass = 0;
	this->m_gravityScale = 1;
	this->m_isKinematic = false;
}

void CRigidbody::SetIsKinematic(bool isKinematic)
{
	m_isKinematic = isKinematic;
	if(isKinematic)
	{
		m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	}
}

void CRigidbody::Update(DWORD dt)
{
	if (m_isKinematic) return;

	auto pTransform = m_pGameObject->GetComponent<CTransform>();
	if (pTransform)
		pTransform->PlusPosition(m_velocity * dt);
}

void CRigidbody::Render()
{
}

CRigidbody* CRigidbody::Clone() const
{
	return new CRigidbody(*this);
}
