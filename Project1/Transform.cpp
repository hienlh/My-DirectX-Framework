#include "Transform.h"

using namespace Framework::Component;

//void CTransform::Update(Vector3 position, Vector3 rotation, Vector3 scale)
//{
//	m_position = position;
//	m_rotation = rotation;
//	m_scale = scale;
//}

bool CTransform::Init(Vector3 position, Vector3 rotation, Vector3 scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_localScale = local_scale;
	return true;
}

	this->m_position = VECTOR3_ZERO;
	this->m_rotation = VECTOR3_ZERO;
	this->m_localScale = VECTOR3_ONE;

	return true;
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
