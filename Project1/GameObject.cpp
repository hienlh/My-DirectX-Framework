#include "GameObject.h"
#include <unordered_map>
#include "Renderer.h"
#include <functional>

using namespace Framework::Object;

bool CGameObject::AddComponent(EBuilderType componentType,
                               UBuilderData data)
{
	SBuilder builder(componentType, data);

	// Use map instead of switch case
	std::unordered_map<EBuilderType, std::function<bool()>> callback = {
		{
			EBuilderType::RENDERER,
			[&]()
			{
				if (!m_rendererComponent)
				{
					m_rendererComponent = reinterpret_cast<Component::CRenderer*>(CComponent::Instantiate(builder));
					return true;
				}
				else
					return false;
			}
		}
	};

	// Invoke the command corresponding to the builder
	return callback[componentType]();
}

bool CGameObject::RemoveComponent(EBuilderType componentType)
{
	// Use map instead of switch case
	std::unordered_map<EBuilderType, std::function<bool()>> callback = {
		{
			EBuilderType::RENDERER,
			[&]()
			{
				if (m_rendererComponent)
				{
					CComponent::Release(reinterpret_cast<CComponent*&>(m_rendererComponent));
					return true;
				}
				else
					return false;
			}
		}
	};

	// Invoke the command corresponding to the builder
	return callback[componentType]();
}

bool CGameObject::Init()
{
	m_rendererComponent = nullptr;
	return true;
}

void CGameObject::Destroy()
{
	if (m_rendererComponent)
		Component::CRenderer::Release(m_rendererComponent);
}

void CGameObject::Update()
{
}

CGameObject* CGameObject::Instantiate(const SBuilder& builder)
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);

	if (!instance->Init())
		SAFE_DELETE(instance);

	return instance;
}

void CGameObject::Release(CGameObject*& instance)
{
	instance->Destroy();
	SAFE_DELETE(instance);
}