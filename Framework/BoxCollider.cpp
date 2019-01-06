#include "stdafx.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Graphic.h"
#include "GameManager.h"
#include "Renderer.h"

using namespace Framework;

CBoxCollider::CBoxCollider(const CBoxCollider &boxCollider) : CCollider(boxCollider)
{
	m_Size = boxCollider.m_Size;
}

CBoxCollider::CBoxCollider(CGameObject* gameObject) : CCollider(gameObject)
{
	m_Size = Vector2(1, 1);
	if (const auto renderer = m_pGameObject->GetComponent<CRenderer>())
	{
		m_Size = renderer->GetSize();
	}
	m_Offset = Vector2(0, 0);
	m_Bound = Bound(Vector2(0, 0), m_Size);
}

CBoxCollider* CBoxCollider::SetSize(Vector2 size)
{
	m_Size = size;
	m_Bound = Bound(Vector2(0, 0), m_Size);
	if(m_pGameObject->GetScene())
		m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	return this;
}

CBoxCollider* CBoxCollider::PlusSize(Vector2 size)
{
	SetSize(m_Size + size);
	return this;
}

void CBoxCollider::Update(DWORD dt)
{
	if (m_AutoBoundSize)
		SetSize(m_pGameObject->GetComponent<CRenderer>()->GetSprite()->GetSize());
}

void CBoxCollider::Render()
{
	CGraphic::GetInstance()->DrawRectangle(GetBoundGlobal());
}