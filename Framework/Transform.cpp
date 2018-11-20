#include "stdafx.h"
#include "Transform.h"

using namespace Framework;

CTransform::CTransform(CGameObject* game_object, Vector2 position, Vector3 rotation, Vector2 local_scale) : CComponent(game_object)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_localScale = local_scale;
}

bool CTransform::Init(Vector2 position, Vector3 rotation, Vector2 scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_localScale = scale;
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

