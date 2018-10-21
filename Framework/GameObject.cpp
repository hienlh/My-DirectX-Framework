#include "GameObject.h"
#include <functional>
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

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Release()
{
}

CGameObject* CGameObject::Instantiate()
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);

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
	{
		component->Update(dt);
	}
}

void CGameObject::Render()
{
	GetComponent<CRenderer>()->Render();
}
