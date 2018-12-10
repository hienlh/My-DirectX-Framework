#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Animator.h"

using namespace Framework;

DWORD CGameObject::staticID = 0;

CGameObject::CGameObject(LPCWSTR name, Vector2 position, bool addIntoCurrentScene)
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

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}

void CGameObject::Update(DWORD dt)
{
	for (auto component : m_pComponents)
		component.second->Update(dt);
}

void CGameObject::Render()
{
	for (auto component : m_pComponents)
		component.second->Render();
}

tinyxml2::XMLElement* CGameObject::ToXmlElement(tinyxml2::XMLDocument& doc) const
{
	tinyxml2::XMLElement *result = doc.NewElement("Node");

	result->SetAttribute("name", m_Name);

	//TODO ToXmlElement GameObject
	return nullptr;
}
