#include "Component.h"
#include "GameObject.h"
#include "Animator.h"

Framework::CGameObject* _gameObject = nullptr;

// Create new instance
Framework::CComponent* Framework::CComponent::Instantiate(SBuilder builder)
{
	if (builder.type == EObjectType::RENDERER)
		return CRenderer::Instantiate(builder.data);
	else if (builder.type == EObjectType::TRANSFORM)
		return CTransform::Instantiate(builder.data);
	else if (builder.type == EObjectType::ANIMATOR)
		return CAnimator::Instantiate(builder.data);
	else
		return nullptr;
}

// Release instance
void Framework::CComponent::Destroy(CComponent * &instance)
{
	if (instance->m_type == EObjectType::RENDERER)
		CRenderer::Destroy(reinterpret_cast<CRenderer*&>(instance));
	else if (instance->m_type == EObjectType::TRANSFORM)
		CTransform::Destroy(reinterpret_cast<CTransform*&>(instance));
	else if (instance->m_type == EObjectType::ANIMATOR)
		CAnimator::Destroy(reinterpret_cast<CAnimator*&>(instance));
}
