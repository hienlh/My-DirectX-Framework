#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Animator.h"

using namespace Framework;

bool CGameObject::Init()
{
	bool result = false;
	do
	{
		if (!this->AddComponent<CTransform>())
			break;

		CScene* pScene = CGameManager::GetInstance()->GetCurrentScene();
		if (pScene)
			pScene->AddGameObject(this);

		result = true;
	} while (false);

	return result;
}

void CGameObject::Release()
{
	for (CComponent* pComponent : m_pComponents)
		SAFE_DELETE(pComponent);
}

CGameObject* CGameObject::Instantiate()
{
	CGameObject* instance = nullptr;
	bool result = false;
	do
	{
		SAFE_ALLOC(instance, CGameObject);

		if (!instance->Init())
			break;

		result = true;
	} while (false);

	if (!result)
	{
		if (instance)
			instance->Release();
		SAFE_DELETE(instance);
	}
	return instance;
}

CGameObject* CGameObject::Instantiate(LPCWSTR name, Vector2 position)
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);


	if (!instance->Init())
		SAFE_DELETE(instance);

	instance->m_Name = name;
	instance->GetComponent<CTransform>()->Set_Position(position);

	return instance;
}

CGameObject* CGameObject::Instantiate(Vector2 position)
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);


	if (!instance->Init())
		SAFE_DELETE(instance);

	instance->GetComponent<CTransform>()->Set_Position(position);

	return instance;
}

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}

void CGameObject::Update(DWORD dt)
{
	for (auto component : m_pComponents)
		component->Update(dt);
}

void CGameObject::Render()
{
	for (auto component : m_pComponents)
		component->Render();
}