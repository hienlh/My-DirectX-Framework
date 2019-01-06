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
	m_limitedArea = rigidbody.m_limitedArea;
	m_needUpdate = rigidbody.m_needUpdate;
}

CRigidbody* CRigidbody::SetVelocity(const float &x, const float &y)
{
	if (fabs(x - MAX_VELOCITY) > EPSILON)
		m_velocity.x = x;
	if (fabs(y - MAX_VELOCITY) > EPSILON)
		m_velocity.y = y;
	return this;
}

CRigidbody* CRigidbody::SetIsKinematic(const bool& isKinematic)
{
	m_isKinematic = isKinematic;
	if(isKinematic)
	{
		//Add into the scene to change quadTree
		m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	}
	return this;
}

CRigidbody* CRigidbody::SetLimitedArea(const Rect& limitedArea)
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
		if(m_pGameObject->CheckAddedComponent<CBoxCollider>())
		 	CGraphic::GetInstance()->DrawRectangle(m_pGameObject->GetComponent<CCollider>()->GetBoundArea(), D3DCOLOR_XRGB(0, 0, 255));
		else CGraphic::GetInstance()->DrawRectangle(m_limitedArea, D3DCOLOR_XRGB(0, 0, 255));
	}
}
