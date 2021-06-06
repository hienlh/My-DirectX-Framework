#include "stdafx.h"
#include "Transform.h"
#include "GameObject.h"

using namespace Framework;

CTransform::CTransform(const CTransform& transform) : CComponent(transform)
{
	SetParent(transform.m_pParent);
	m_position = transform.m_position;
	m_rotation = transform.m_rotation;
	m_scale = transform.m_scale;
	m_Name = transform.m_Name;
}

CTransform::CTransform(CGameObject* game_object, Vector2 position, Vector3 rotation, Vector2 scale) : CComponent(game_object)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
}


CTransform& CTransform::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	/*if (const auto pTran = dynamic_cast<const CTransform*>(&component)) {
		SetParent(pTran->m_pParent);
		m_position = pTran->m_position;
		m_rotation = pTran->m_rotation;
		m_scale = pTran->m_scale;
		m_Name = pTran->m_Name;
	}*/

	return *this;
}

/**
 * \brief Get Position
 * \return Position in the world space
 */
Vector2 CTransform::Get_Position() const
{ 
	if (m_pParent)
		return m_position + m_pParent->Get_Position();

	return m_position;
}

Vector3 CTransform::Get_Rotation() const
{
	if (m_pParent)
		return m_rotation + m_pParent->Get_Rotation();

	return m_rotation;
}

Vector2 CTransform::Get_Scale() const
{
	Vector2 result = m_scale;

	if (m_pParent) {
		const Vector2 parentScale = m_pParent->Get_Scale();
		result = Vector2(result.x * parentScale.x, result.y * parentScale.y);
	}

	return result;
}

/**
 * \brief Set position
 * \param position Value of position
 * \param inWorldSpace this value of position is in world space or local
 */
CTransform* CTransform::Set_Position(const Vector2 &position, const bool &inWorldSpace)
{
	m_position = position;
	if (inWorldSpace)
	{
		m_position -= (m_pParent ? m_pParent->Get_Position() : Vector2(0, 0));
	}
	m_pGameObject->GetScene()->AddColliderObject(m_pGameObject);
	return this;
}

CTransform* CTransform::Set_Rotation(const Vector3 &rotation)
{
	m_rotation = rotation - (m_pParent ? m_pParent->Get_Rotation() : Vector3(0, 0, 0));
	return this;
}

CTransform* CTransform::Set_Scale(const Vector2 &scale)
{
	m_scale = scale;
	return this;
}

CTransform* CTransform::SetParent(CTransform* parent)
{
	if (m_pParent) {
		m_pParent->m_pChildren.erase(this); //Erase this in child list of parent
		m_position += m_pParent->Get_Position();
		m_rotation += m_pParent->Get_Rotation();
	}

	if(parent)
	{
		m_position -= parent->Get_Position();
		m_rotation -= parent->Get_Rotation();
		parent->m_pChildren.insert(this);
	}
	m_pParent = parent;
	return this;
}

CTransform* CTransform::SetParent(CGameObject* parentGameObject)
{
	if(parentGameObject)
		SetParent(parentGameObject->GetComponent<CTransform>());
	return this;
}

bool CTransform::Init(Vector2 position, Vector3 rotation, Vector2 scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
	return true;
}

void CTransform::Release()
{
}

CTransform* CTransform::Instantiate(Vector2 position)
{
	CTransform* instance = nullptr;
	SAFE_ALLOC(instance, CTransform);
	if (!instance->Init(position))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

void CTransform::Destroy(CTransform *instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
