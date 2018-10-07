#include "GameObject.h"
#include <unordered_map>
#include "Renderer.h"
#include <functional>
#include "GameManager.h"

using namespace Framework::Object;

bool CGameObject::AddComponent(SBuilder builder)
{
	bool result = false;

	if (builder.builderType == EObjectType::RENDERER && !m_rendererComponent)
	{
		m_rendererComponent = reinterpret_cast<Component::CRenderer*>(CComponent::Instantiate(builder));
		result = true;
	}
	if (builder.builderType == EObjectType::TRANSFORM && !m_transformComponent)
	{
		m_transformComponent = reinterpret_cast<Component::CTransform*>(CComponent::Instantiate(builder));
		result = true;
	}

	return result;
}

bool CGameObject::RemoveComponent(EObjectType type)
{
	bool result = false;

	if (type == EObjectType::RENDERER && m_rendererComponent)
	{
		CComponent::Destroy(reinterpret_cast<CComponent*&>(m_rendererComponent));
		result = true;
	}
	if (type == EObjectType::TRANSFORM && m_transformComponent)
	{
		CComponent::Destroy(reinterpret_cast<CComponent*&>(m_transformComponent));
		result = true;
	}

	return result;
}

bool CGameObject::Init()
{
	m_rendererComponent = nullptr;
	m_transformComponent = nullptr;

	return true;
}

void CGameObject::Release()
{
	if (m_rendererComponent)
		Component::CRenderer::Destroy(m_rendererComponent);

	if (m_transformComponent)
		Component::CTransform::Destroy(m_transformComponent);
}

CGameObject* CGameObject::Instantiate()
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);

	instance->m_type = EObjectType::GAME_OBJECT;

	if (!instance->Init())
		SAFE_DELETE(instance);
	
	return instance;
	//GameManager::IGameManager::AddGameObject(instance);		
}

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}

void CGameObject::Update()
{
	if (m_rendererComponent)
	{
		//m_rendererComponent->Update(m_transformComponent->Get_Position());
	}

	if (m_transformComponent)
	{
		//m_transformComponent->Update();
	}
}
