#include "stdafx.h"
#include "Transform.h"
#include "GameObject.h"

using namespace Framework;

CTransform::CTransform(CGameObject* game_object, Vector2 position, Vector3 rotation, Vector2 scale) : CComponent(game_object)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
}

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

CTransform* CTransform::Set_Position(Vector2 position)
{
	m_position = position - (m_pParent ? m_pParent->Get_Position() : Vector2(0, 0));
	return this;
}

CTransform* CTransform::Set_Rotation(Vector3 rotation)
{
	m_rotation = rotation - (m_pParent ? m_pParent->Get_Rotation() : Vector3(0, 0, 0));
	return this;
}

CTransform* CTransform::Set_Scale(Vector2 scale)
{
	m_scale = scale;
	return this;
}

CTransform* CTransform::SetParent(CTransform* parent)
{
	m_position = m_position + (m_pParent ? m_pParent->Get_Position() - parent->Get_Position() : -parent->Get_Position());
	m_rotation = m_rotation + (m_pParent ? m_pParent->Get_Rotation() - parent->Get_Rotation() : -parent->Get_Rotation());

	m_pParent = parent;
	return this;
}

CTransform* CTransform::SetParent(CGameObject* parentGameObject)
{
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

void CTransform::Update(DWORD dt)
{
}

void CTransform::Render()
{
}

