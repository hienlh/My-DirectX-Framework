#include "Object.h"
#include <functional>
#include <unordered_map>
#include "GameObject.h"

using namespace Framework::Object;

CObject* CObject::Instantiate(const SBuilder& builder)
{
	CObject* instance = nullptr;

	if (builder.m_componentType == EBuilderType::GAMEOBJECT)
		instance = CGameObject::Instantiate(builder);
	else if (builder.m_componentType == EBuilderType::RENDERER || builder.m_componentType == EBuilderType::TRANSFORM)
		instance = CComponent::Instantiate(builder);

	if (instance)
		instance->m_builderType = builder.m_componentType;

	return instance;
}

void CObject::Release(CObject* & instance)
{
	if (instance->m_builderType == EBuilderType::RENDERER)
		CComponent::Release(reinterpret_cast<CComponent*&>(instance));
}
