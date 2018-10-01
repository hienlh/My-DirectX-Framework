#include "Component.h"
#include <functional>
#include <unordered_map>
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

using namespace Framework::Component;

void Framework::Object::CComponent::Update()
{
}

// Create new instance
Framework::Object::CComponent* Framework::Object::CComponent::Instantiate(const SBuilder &builder)
{
	// Use map instead of switch case
	std::unordered_map<EBuilderType, std::function<CComponent*()>> callback = {
		{
			EBuilderType::RENDERER,
			[&]()
			{
				return CRenderer::Instantiate(builder.m_data.rendererBuilder.d3ddev,
															  builder.m_data.rendererBuilder.texturePath);
			}
		},
		{
			EComponentType::TRANSFORM,
			[&]()
			{
				pComponent = CTransform::Instantiate(builder.m_data.transformBuilder.position,
													 builder.m_data.transformBuilder.rotation,
													 builder.m_data.transformBuilder.scale);
				pComponent->m_componentType = EComponentType::TRANSFORM;
			}
		}
	};

	// Invoke the command corresponding to the builder
	return callback[builder.m_componentType]();
}

// Release instance
void Framework::Object::CComponent::Release(CComponent * &instance)
{
	// Use map instead of switch case
	std::unordered_map<EBuilderType, std::function<void()>> callback = {
		{
			EBuilderType::RENDERER,
			[&]()
			{
				CRenderer::Release(reinterpret_cast<CRenderer*&>(instance));
			}
		}
	};

	// Invoke the command corresponding to the builder
	callback[instance->m_builderType]();
}
