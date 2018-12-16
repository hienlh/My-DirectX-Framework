#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Animator.h"
#include "Transform.h"
#include "ResourceManager.h"

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
}

CGameObject::CGameObject(std::string name, Vector2 position, bool addIntoCurrentScene)
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

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}

void CGameObject::Update(DWORD dt)
{
	CTransform * transform = dynamic_cast<CTransform *>(m_pComponents[typeid(CTransform).name()]);

	const Vector2 prePos = transform->Get_Position();

	for (auto component : m_pComponents)
		if(component.second->GetIsActive())
			component.second->Update(dt);

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

/**
 * \brief Clone GameObject will auto add into the scene
 */
CGameObject* CGameObject::Clone() const
{
	const auto result = new CGameObject(*this);
	CGameManager::GetInstance()->GetCurrentScene()->AddGameObject(result);
	return result;
}

tinyxml2::XMLElement* CGameObject::ToXmlElement(tinyxml2::XMLDocument& doc) const
{
	//TODO ToXmlElement GameObject
	return nullptr;
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
CGameObject* CGameObject::Instantiate(CGameObject* gameObject, CGameObject* parent, Vector2 position, Vector3 rotation,
	bool instantiateInWorldSpace)
{
	auto *result = gameObject->Clone();

	result->GetComponent<CTransform>()
		->SetParent(parent)
		->Set_Position(position, instantiateInWorldSpace)
		->Set_Rotation(rotation);

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
CGameObject* CGameObject::Instantiate(std::string prefabName, CGameObject* parent, Vector2 position, Vector3 rotation,
	bool instantiateInWorldSpace)
{
	auto a = CResourceManager::GetInstance();
	CGameObject* gameObject = a->GetPrefab(prefabName);
	if (!gameObject) return nullptr;
	
	return Instantiate(gameObject, parent, position, rotation, instantiateInWorldSpace);
}
