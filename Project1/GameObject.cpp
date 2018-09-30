#include "GameObject.h"
#include <unordered_map>
#include "Renderer.h"
#include <functional>

using namespace Framework::Object;

bool CGameObject::AddComponent(Framework::Component::EComponentType componentType,
                               Framework::Component::UBuilderData data)
{
	bool result = false;
	// Use map instead of switch case
	std::unordered_map<Component::EComponentType, std::function<void()>> callback = {
		{
			Component::EComponentType::RENDERER,
			[&]()
			{
				if (!m_rendererComponent)
				{
					Component::SBuilder builder(componentType, data);
					m_rendererComponent = reinterpret_cast<Component::CRenderer*>(Component::CComponent::Instantiate(
						builder));
					result = true;
				}
			}
		}
	};

	// Invoke the command corresponding to the builder
	callback[componentType]();

	return result;
}

bool CGameObject::RemoveComponent(Framework::Component::EComponentType componentType)
{
	bool result = false;
	// Use map instead of switch case
	std::unordered_map<Component::EComponentType, std::function<void()>> callback = {
		{
			Component::EComponentType::RENDERER,
			[&]()
			{
				if (!m_rendererComponent)
				{
					Component::CRenderer::Release(m_rendererComponent);
				}
			}
		}
	};

	// Invoke the command corresponding to the builder
	callback[componentType]();

	return result;
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

CGameObject* CGameObject::Instantiate()
{
	CGameObject* pGameObject = nullptr;
	SAFE_ALLOC(pGameObject, CGameObject);

	return pGameObject;
}

void CGameObject::Release(CGameObject* pObject)
{
	pObject->Destroy();
	SAFE_DELETE(pObject);
}

//
//void CGameObject::Render(CDirect3D *pDirect3D)
//{
//	pDirect3D->Draw(m_x, m_y, m_texture);
//}
