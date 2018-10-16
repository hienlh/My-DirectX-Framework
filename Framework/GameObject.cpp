#include "GameObject.h"
#include <functional>
#include "GameManager.h"

using namespace Framework;


//Temp for deadline
bool CGameObject::leftBlockMoveDown = true;
bool CGameObject::rightBlockMoveDown = true;

bool CGameObject::AddComponent(SBuilder builder)
{
	bool result = false;
	if (builder.builderType == EObjectType::RENDERER && !m_rendererComponent)
	{
		m_rendererComponent = reinterpret_cast<CRenderer*>(CComponent::Instantiate(builder));
		if(m_rendererComponent)
			m_rendererComponent->SetGameObject(this);
		result = true;
	}
	if (builder.builderType == EObjectType::TRANSFORM && !m_transformComponent)
	{
		m_transformComponent = reinterpret_cast<CTransform*>(CComponent::Instantiate(builder));
		if (m_transformComponent)
			m_transformComponent->SetGameObject(this);
		result = true;
	}
	return result;
}

bool CGameObject::AddComponent(EObjectType type)
{
	bool result = false;
	if (type == EObjectType::RENDERER && !m_rendererComponent)
	{
		m_rendererComponent = new CRenderer(this);
		result = true;
	}
	if (type == EObjectType::TRANSFORM && !m_transformComponent)
	{
		m_transformComponent = new CTransform(this);
		result = true;
	}
	return result;
}

//template <class T>
//bool CGameObject::AddComponent()
//{
//
//	return false;
//}
//template <> bool CGameObject::AddComponent<CRenderer>()
//{
//	if (m_rendererComponent) return true;
//
//	m_rendererComponent = new CRenderer(this);
//	return m_rendererComponent!=nullptr;
//}
//template <> bool CGameObject::AddComponent<CTransform>()
//{
//	if (m_transformComponent) return true;
//
//	m_transformComponent = new CTransform(this);
//	return m_transformComponent != nullptr;
//}
//template <> bool CGameObject::AddComponent<CRigidbody>()
//{
//	if (m_rigidbodyComponent) return true;
//
//	m_rigidbodyComponent = new CRigidbody(this);
//	return m_rigidbodyComponent != nullptr;
//}

template <class Type>
Type* CGameObject::GetComponent()
{
	using std::is_same;
	if ( is_same<Type, CRenderer>::value) {
		return m_rigidbodyComponent;
	}
	if (is_same<Type, CTransform>::value){
		return m_transformComponent;
	}
	if (is_same<Type, CRigidbody>::value)
	{
		return m_rendererComponent;
	}
	return nullptr;
}
template <> CTransform* CGameObject::GetComponent<CTransform>()
{
	return m_transformComponent;
}
template <> CRenderer* CGameObject::GetComponent<CRenderer>()
{
	return m_rendererComponent;
}
template <> CRigidbody* CGameObject::GetComponent<CRigidbody>()
{
	return m_rigidbodyComponent;
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
	m_rigidbodyComponent = nullptr;

	return true;
}

void CGameObject::Release()
{
	if (m_rendererComponent)
		CRenderer::Destroy(m_rendererComponent);
	if (m_transformComponent)
		CTransform::Destroy(m_transformComponent);
	if (m_rigidbodyComponent)
		SAFE_DELETE(m_rigidbodyComponent);
}

CGameObject* CGameObject::Instantiate()
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);

	instance->m_type = EObjectType::GAME_OBJECT;

	if (!instance->Init())
		SAFE_DELETE(instance);

	auto scene = CGameManager::GetInstance()->GetCurrentScene();
	if (scene)
		scene->AddGameObject(instance);

	return instance;
}

CGameObject* CGameObject::Instantiate(Vector2 position)
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);


	if (!instance->Init())
		SAFE_DELETE(instance);

	instance->m_transformComponent = CTransform::Instantiate(position);
	auto scene = CGameManager::GetInstance()->GetCurrentScene();
	if (scene)
		scene->AddGameObject(instance);

	return instance;
}

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}
void CGameObject::Update(DWORD dt)
{
	if (m_rendererComponent)
	{
		m_rendererComponent->Update(dt);
	}

	if (m_transformComponent)
	{
		m_transformComponent->Update(dt);
	}

	if (m_rigidbodyComponent)
	{
		m_rigidbodyComponent->Update(dt);
	}

	for (auto component : m_extendComponents)
	{
		component->Update(dt);
	}
}

void CGameObject::Render()
{
	m_rendererComponent->Render();
}
