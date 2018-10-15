#include "stdafx.h"
#include "Transform.h"

using namespace Framework;

//void CTransform::Update(Vector3 position, Vector3 rotation, Vector3 scale)
//{
//	m_position = position;
//	m_rotation = rotation;
//	m_scale = scale;
//}

bool CTransform::Init(Vector2 position, Vector2 rotation, Vector2 scale)
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
	instance->m_type = EObjectType::TRANSFORM;
	if (!instance->Init(position))
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

CTransform* CTransform::Instantiate(Framework::UObjectData data)
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

