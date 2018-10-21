#include "GameObject.h"
#include <functional>
#include "Scene.h"
#include "GameManager.h"

using namespace Framework;

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

//template <class Type>
//Type* CGameObject::GetComponent()
//{
//	using std::is_same;
//	if ( is_same<Type, CRenderer>::value) {
//		return m_rigidbodyComponent;
//	}
//	if (is_same<Type, CTransform>::value){
//		return m_transformComponent;
//	}
//	if (is_same<Type, CRigidbody>::value)
//	{
//		return m_rendererComponent;
//	}
//	return nullptr;
//}
//template <> CTransform* CGameObject::GetComponent<CTransform>()
//{
//	return m_transformComponent;
//}
//template <> CRenderer* CGameObject::GetComponent<CRenderer>()
//{
//	return m_rendererComponent;
//}
//template <> CRigidbody* CGameObject::GetComponent<CRigidbody>()
//{
//	return m_rigidbodyComponent;
//}
bool CGameObject::AddComponent(SBuilder builder)
{
	bool result = false;
	if (builder.type == EObjectType::RENDERER && !m_rendererComponent)
	{
		m_rendererComponent = reinterpret_cast<CRenderer*>(CComponent::Instantiate(builder));
		if(m_rendererComponent)
			m_rendererComponent->SetParentObject(this);
		result = true;
	}
	else if (builder.type == EObjectType::TRANSFORM && !m_transformComponent)
	{
		m_transformComponent = reinterpret_cast<CTransform*>(CComponent::Instantiate(builder));
		if (m_transformComponent)
			m_transformComponent->SetParentObject(this);
		result = true;
	}
	else if (builder.type == EObjectType::ANIMATOR && !m_animatorComponent)
	{
		m_animatorComponent = reinterpret_cast<CAnimator*>(CComponent::Instantiate(builder));
		if (m_animatorComponent)
			m_animatorComponent->SetParentObject(this);
		result = true;
	}

	return result;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Release()
{
}

CGameObject* CGameObject::Instantiate(Vector2 position)
{
	CGameObject* instance = nullptr;
	bool result = false;
	do
	{
		SAFE_ALLOC(instance, CGameObject);

		if (!instance->Init())
			break;

	if (!instance->Init())
		SAFE_DELETE(instance);

	auto scene = CGameManager::GetInstance()->GetCurrentScene();
	if (scene)
		scene->AddGameObject(instance);
		Framework::UObjectData data = { {} };
		data.transformData = { position, VECTOR2_ZERO, VECTOR2_ONE };
		instance->AddComponent({ EObjectType::TRANSFORM, data });
		if (!instance->m_transformComponent)
			break;
		
		CScene* pScene = CGameManager::GetInstance()->GetCurrentScene();
		if (!pScene)
			break;
		
		pScene->AddGameObject(instance);

		result = true;
	} while (false);

	if (!result)
	{
		if (instance)
			instance->Release();
		SAFE_DELETE(instance);

	instance->AddComponent<CTransform>()->Set_Position(position);
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
	for (auto component : m_Components)
		component->Update(dt);
	
	if (m_transformComponent)
		m_transformComponent->Update(dt);
	
	if (m_rigidbodyComponent)
		m_rigidbodyComponent->Update(dt);
	
	if (m_animatorComponent)
		m_animatorComponent->Update(dt);
}

void CGameObject::Render()
{
	if (m_rendererComponent)
		m_rendererComponent->Render();

	if (m_animatorComponent)
		m_animatorComponent->Render();
}