#include "Transform.h"

using namespace Framework::Component;

bool Framework::Component::CTransform::Init(const Vector2 position, const Vector3 rotation, const Vector3 local_scale)
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
	instance->m_type = Object::EObjectType::TRANSFORM;
	if (!instance->Init(position))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

CTransform* CTransform::Instantiate(Framework::Object::UObjectData data)
{
	CTransform* instance = nullptr;
	SAFE_ALLOC(instance, CTransform);
	instance->m_type = Object::EObjectType::TRANSFORM;
	if (instance->Init(data.transformData.position, data.transformData.rotation, data.transformData.scale))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

void Framework::Component::CTransform::Destroy(CTransform *instance)
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
