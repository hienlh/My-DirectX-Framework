#include "stdafx.h"
#include "Rigidbody.h"

#include "GameObject.h"

using namespace Framework;

CRigidbody::CRigidbody(Framework::CGameObject * gameObject)
{
	this->m_parentObject = gameObject;
	this->_velocity = Vector2(0, 0);
	this->_mass = 0;
	this->_gravityScale = 1;
	this->_isKinematic = false;
}

void CRigidbody::Update(DWORD dt)
{
	CTransform* pTransform = reinterpret_cast<CGameObject*>(m_parentObject)->GetTransform();
	if (pTransform)
		pTransform->m_position += _velocity * dt / 10;
}

void CRigidbody::Render()
{
}
