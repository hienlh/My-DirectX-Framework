#include "stdafx.h"
#include "BoxCollider.h"
#include "GameObject.h"

using namespace Framework;

CBoxCollider::CBoxCollider(CGameObject* gameObject) : CCollider(gameObject)
{
	const auto transform = m_pGameObject->GetComponent<CTransform>();
	m_Size = Vector2(1, 1);
	if (const auto renderer = m_pGameObject->GetComponent<CRenderer>())
	{
		m_Size = renderer->GetSize();
	}
	m_Offset = Vector2(0, 0);
	m_Bound = Bound(Vector2(0, 0), m_Size);
}

void CBoxCollider::SetSize(Vector2 size)
{
	m_Size = size;
	m_Bound = Bound(Vector2(0, 0), m_Size);
}

void CBoxCollider::Update(DWORD dt)
{
}

void CBoxCollider::Render()
{
}

