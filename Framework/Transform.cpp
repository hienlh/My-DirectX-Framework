#include "Transform.h"

using namespace Framework;

CTransform::CTransform(CGameObject* game_object, Vector2 position, Vector3 rotation, Vector3 local_scale) : CComponent(game_object)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_localScale = local_scale;
}

bool CTransform::Init(const Vector2 position, const Vector3 rotation, const Vector3 local_scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_localScale = local_scale;
	return true;
}

void CTransform::Release()
{

}

CTransform* CTransform::Instantiate(Vector2 position)
{
	CTransform* instance = nullptr;
	SAFE_ALLOC(instance, CTransform);
	instance->m_type = EObjectType::TRANSFORM;
	if (!instance->Init(position))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

CTransform* CTransform::Instantiate(UObjectData data)
{
	CTransform* instance = nullptr;
	SAFE_ALLOC(instance, CTransform);
	instance->m_type = EObjectType::TRANSFORM;
	if (instance->Init(data.transformData.position, data.transformData.rotation, data.transformData.scale))
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
