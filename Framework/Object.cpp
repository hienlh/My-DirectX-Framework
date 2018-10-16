#include "Object.h"
#include "GameObject.h"

using namespace Framework;

CObject* CObject::Instantiate(SBuilder builder)
{
	if (builder.builderType == EObjectType::GAME_OBJECT)
		return CGameObject::Instantiate();
	else if (builder.builderType == EObjectType::RENDERER || builder.builderType == EObjectType::TRANSFORM)
		return CComponent::Instantiate(builder);
	else
		return nullptr;
}

void CObject::Destroy(CObject* & instance)
{
	if (instance->m_type == EObjectType::GAME_OBJECT)
		CGameObject::Destroy(reinterpret_cast<CGameObject*&>(instance));
	else if (instance->m_type == EObjectType::RENDERER || instance->m_type == EObjectType::TRANSFORM)
		CComponent::Destroy(reinterpret_cast<CComponent*&>(instance));
}
