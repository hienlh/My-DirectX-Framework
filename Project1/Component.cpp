#include "Component.h"
#include "Renderer.h"
#include "Transform.h"

using namespace Framework::Component;


Framework::Object::CGameObject* _gameObject = nullptr;

// Create new instance
Framework::Object::CComponent* Framework::Object::CComponent::Instantiate(SBuilder builder)
{
	if (builder.builderType == EObjectType::RENDERER)
		return CRenderer::Instantiate(builder.builderData);
	else if (builder.builderType == EObjectType::TRANSFORM)
		return CTransform::Instantiate(builder.builderData);
	else
		return nullptr;
}

// Release instance
void Framework::Object::CComponent::Destroy(CComponent * &instance)
{
	if (instance->m_type == EObjectType::RENDERER)
		CRenderer::Destroy(reinterpret_cast<CRenderer*&>(instance));
	else if (instance->m_type == EObjectType::TRANSFORM)
		CTransform::Destroy(reinterpret_cast<CTransform*&>(instance));
}
