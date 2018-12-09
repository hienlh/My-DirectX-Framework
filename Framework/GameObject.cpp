#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Animator.h"

using namespace Framework;

CGameObject::CGameObject(LPCWSTR name, Vector2 position, bool addIntoCurrentScene)
{
	if (!this->Init())
		delete this;

	if (addIntoCurrentScene) {
		CScene* pScene = CGameManager::GetInstance()->GetCurrentScene();
		if (pScene)
			pScene->AddGameObject(this);
	}

	this->m_Name = name;
	this->GetComponent<CTransform>()->Set_Position(position);
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