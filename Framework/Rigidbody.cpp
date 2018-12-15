#include "stdafx.h"
#include "Rigidbody.h"

#include "GameObject.h"
#include "Graphic.h"

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

CRigidbody* CRigidbody::SetIsKinematic(bool isKinematic)
{
	m_isKinematic = isKinematic;
	if(isKinematic)
	{
		//Add to scene to change quadTree
		m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	}
	return this;
}

CRigidbody* CRigidbody::SetLimitedArea(Rect limitedArea)
{
	//If object is static, not update limited area
	if (!m_isKinematic) {
		m_limitedArea = limitedArea;

		//Add to scene to change quadTree
		m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	}
	return this;
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
	if(m_limitedArea != Bound(0,0,0,0))
	{
		CGraphic::GetInstance()->DrawRectangle(m_limitedArea, D3DCOLOR_XRGB(0, 0, 255));
	}
}

CRigidbody* CRigidbody::Clone() const
{
	return new CRigidbody(*this);
}
