#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Animator.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MonoBehavier.h"

using namespace Framework;

DWORD CGameObject::staticID = 0;

CGameObject::CGameObject(const CGameObject& gameObject) : CObject(gameObject)
{
	this->m_id = ++staticID;
	this->m_Name += std::to_string(this->m_id);

	for (const std::pair<const std::basic_string<char>, CComponent*> component : gameObject.m_pComponents)
	{
		AddComponent(component.second->Clone());
	}
	CGameManager::GetInstance()->GetCurrentScene()->AddGameObject(this);
}

CGameObject::CGameObject(const bool& addIntoCurrentScene, const std::string& name, const Vector2& position)
{
	if (!this->Init())
		delete this;
	this->m_id = ++staticID;
	this->m_Name = name;
	this->GetComponent<CTransform>()->Set_Position(position);

	if (addIntoCurrentScene) {
		CScene* pScene = CGameManager::GetInstance()->GetCurrentScene();
		if (pScene)
			if (!pScene->AddGameObject(this)) delete this;
	}
}

CGameObject::~CGameObject()
{
	for(auto i=m_pComponents.begin();i!=m_pComponents.end();++i)
	{
		SAFE_DELETE((*i).second);
	}

	if(m_pScene)
		m_pScene->RemoveGameObject(this);
}

bool CGameObject::AddComponent(CComponent* component)
{
	bool result = false;
	do
	{
		const std::string typeName = typeid(*component).name();
		if (!m_pComponents.count(typeName))
		{
			m_pComponents[typeName] = component;
			component->SetGameObject(this);

			if (reinterpret_cast<CCollider *> (&component) && m_pScene)
			{
				m_pScene->AddColliderObject(this);
			}
			result = true;
		}
	} while (false);

	return result;
}

bool CGameObject::Init()
{
	bool result = false;
	do
	{
		if (!this->AddComponent<CTransform>())
			break;

		result = true;
	} while (false);

	return result;
}

void CGameObject::Release()
{
	for (auto pComponent : m_pComponents) {
		SAFE_DELETE(pComponent.second);
	}
	m_pComponents.clear();
}

void CGameObject::CheckAfterAddComponent(CComponent* component)
{
	const std::string typeName = typeid(*component).name();
	
	if (typeName == typeid(CAnimator).name() && !CheckAddedComponent<CRenderer>()) {
		AddComponent<CRenderer>();
	}
	
}

CGameObject* CGameObject::GetParent()
{
	if (const auto tmp = dynamic_cast<CTransform*>(m_pComponents[typeid(CTransform).name()])->GetParent())
		return tmp->m_pGameObject;
	return nullptr;
}

Vector2 CGameObject::GetPosition()
{
	return  dynamic_cast<CTransform*>(m_pComponents[typeid(CTransform).name()])->Get_Position();
}

bool CGameObject::IsInCurrentScene() const
{
	return m_pScene == CGameManager::GetInstance()->GetCurrentScene();
}

CGameObject* CGameObject::SetParent(CGameObject* parent)
{
	dynamic_cast<CTransform*>(m_pComponents[typeid(CTransform).name()])->SetParent(parent);

	return this;
}

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}

void CGameObject::Update(const DWORD& dt)
{
	CTransform * transform = dynamic_cast<CTransform *>(m_pComponents[typeid(CTransform).name()]);

	const Vector2 prePos = transform->Get_Position();

	for (auto component : m_pComponents)
		if (component.second->GetIsActive()) {
			component.second->Update(dt);
			if (!component.second->GetGameObject() || !component.second->GetGameObject()->GetIsActive()) return;
		}

	//Reset position of static gameObjects and half-static gameObjects which is moved
	Vector2 curPos = transform->Get_Position();
	if(CheckAddedComponent<CRigidbody>() && curPos != prePos)
	{
		auto rigidBody = GetComponent<CRigidbody>();
		if (rigidBody->GetIsKinematic()) {
			GetComponent<CTransform>()->Set_Position(prePos);
		}
		else if(rigidBody->GetLimitedArea() != Rect(0,0,0,0))
		{
			Rect limitedArea = rigidBody->GetLimitedArea();
			if(!limitedArea.isInside(curPos))
			{
				if(curPos.x < limitedArea.left || curPos.x > limitedArea.right)
				{
					curPos.x = prePos.x;
				}

				if (curPos.y < limitedArea.top || curPos.y > limitedArea.bottom)
				{
					curPos.y = prePos.y;
				}

				transform->Set_Position(curPos);
			}
		}
	}
}

void CGameObject::Render()
{
	for (auto component : m_pComponents)
		if(component.second->GetIsActive())
			component.second->Render();
}

void CGameObject::CopyValue(const CGameObject& object)
{
	for (const std::pair<const std::basic_string<char>, CComponent*> component : object.m_pComponents)
	{
		if (m_pComponents.count(component.first)) {
			(*m_pComponents[component.first]) = (*component.second);
		}
	}
}

bool CGameObject::GetIsActive()
{
	if (const auto parent = this->GetComponent<CTransform>()->GetParent())
			return m_isActive && parent->GetGameObject()->GetIsActive();
	return m_isActive;
}

CGameObject& CGameObject::operator=(const CGameObject& gameObject)
{
	(*this).CObject::operator=(gameObject);

	for (const std::pair<const std::basic_string<char>, CComponent*> component : gameObject.m_pComponents)
	{
		if (m_pComponents.count(component.first)) {
			*m_pComponents[component.first] = *component.second;
		}
	}

	return *this;
}

/**
 * \brief Clones the object original and returns the clone.
 * \param gameObject An existing gameObject that you want to make a copy of.
 * \param parent Parent that will be assigned to the new object.
 * \param position Position for the new object.
 * \param rotation Orientation of the new object.
 * \param instantiateInWorldSpace Pass true when assigning a parent Object to maintain the world position of the Object, instead of setting its position relative to the new parent. Pass false to set the Object's position relative to its new parent.
 * \return CGameObject The instantiated clone.
 */
CGameObject* CGameObject::Instantiate(CGameObject* gameObject, CGameObject* parent, const Vector2& position,
	const Vector3& rotation, const bool& instantiateInWorldSpace)
{
	auto *result = new CGameObject(*gameObject);

	result->GetComponent<CTransform>()
		->SetParent(parent)
		->Set_Position(position, instantiateInWorldSpace)
		->Set_Rotation(rotation);

	if(CGameManager::GetInstance()->IsRunning())
		for (auto component : result->m_pComponents)
		{
			if (auto mono = dynamic_cast<CMonoBehavior*>(component.second))
				mono->Start();
		}

	return result;
}

/**
 * \brief Clones the prefab and returns the clone.
 * \param prefabName Name of the prefab that you want to make a copy of
 * \param parent Parent that will be assigned to the new object.
 * \param position Position for the new object.
 * \param rotation Orientation of the new object.
 * \param instantiateInWorldSpace Pass true when assigning a parent Object to maintain the world position of the Object, instead of setting its position relative to the new parent. Pass false to set the Object's position relative to its new parent.
 * \return CGameObject The instantiated clone.
 */
 CGameObject* CGameObject::Instantiate(const std::string& prefabName, CGameObject* parent, const Vector2& position,
	const Vector3& rotation, const bool& instantiateInWorldSpace)
{
	auto a = CResourceManager::GetInstance();
	CGameObject* gameObject = a->GetPrefab(prefabName);
	if (!gameObject) return nullptr;
	
	return Instantiate(gameObject, parent, position, rotation, instantiateInWorldSpace);
}
