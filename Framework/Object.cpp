#include "Object.h"
#include "GameObject.h"

using namespace Framework;

void CObject::SetParentObject(CObject* pParent)
{
	m_parentObject = pParent;
}

CObject* CObject::Instantiate(SBuilder builder)
{
	if (builder.type == EObjectType::GAME_OBJECT)
		return CGameObject::Instantiate();
	else if (builder.type == EObjectType::RENDERER || builder.type == EObjectType::TRANSFORM || builder.type == EObjectType::ANIMATOR)
		return CComponent::Instantiate(builder);
	else
		return nullptr;
}

void CObject::Destroy(CObject* & instance)
{
	if (instance->m_type == EObjectType::GAME_OBJECT)
		CGameObject::Destroy(reinterpret_cast<CGameObject*&>(instance));
	else if (instance->m_type == EObjectType::RENDERER || instance->m_type == EObjectType::TRANSFORM || instance->m_type == EObjectType::ANIMATOR)
		CComponent::Destroy(reinterpret_cast<CComponent*&>(instance));
}
