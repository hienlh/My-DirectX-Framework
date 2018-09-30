#include "Component.h"
#include <functional>
#include <unordered_map>
#include "Renderer.h"

using namespace Framework::Component;

// Create new instance
CComponent* CComponent::Instantiate(const SBuilder &builder)
{
	CComponent* pComponent = nullptr;
	
	// Use map instead of switch case
	std::unordered_map<EComponentType, std::function<void()>> callback = {
		{
			EComponentType::UNKNOWN,
			[&]()
			{
				pComponent = nullptr;
			}
		},
		{
			EComponentType::RENDERER,
			[&]()
			{
				pComponent = CRenderer::Instantiate(builder.m_data.rendererBuilder.d3ddev,
				                                    builder.m_data.rendererBuilder.texturePath);
				pComponent->m_componentType = EComponentType::RENDERER;
			}
		}
	};

	// Invoke the command corresponding to the builder
	callback[builder.m_componentType]();

	return pComponent;
}

// Release instance
void Framework::Component::CComponent::Release(CComponent * pObject)
{
	// Use map instead of switch case
	std::unordered_map<EComponentType, std::function<void()>> callback = {
		{
			EComponentType::RENDERER,
			[&]()
			{
				CRenderer::Release(reinterpret_cast<CRenderer*>(pObject));
			}
		}
	};

	// Invoke the command corresponding to the builder
	callback[pObject->m_componentType]();
}
