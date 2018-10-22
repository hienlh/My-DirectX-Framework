#include "GameObject.h"
#include <functional>
#include "GameManager.h"

using namespace Framework;

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

CGameObject* CGameObject::Instantiate(String name, Vector2 position)
{
	CGameObject* instance = nullptr;
	SAFE_ALLOC(instance, CGameObject);


	if (!instance->Init())
		SAFE_DELETE(instance);

	instance->m_Name = name;
	instance->AddComponent<CTransform>()->Set_Position(position);

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
	{
		component->Update(dt);
	}
}

void CGameObject::Render()
{
	GetComponent<CRenderer>()->Render();
}
