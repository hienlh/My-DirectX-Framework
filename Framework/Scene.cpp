#include "stdafx.h"
#include "Scene.h"
#include "GameManager.h"
#include "Camera.h"

using namespace Framework;

bool CScene::Init()
{
	InitMainCamera();
	return true;
}

bool CScene::InitMainCamera()
{
	bool result = false;
	do
	{
		m_pMainCamera = CGameObject::Instantiate(L"Main Camera", VECTOR2_ZERO);
		m_pMainCamera->AddComponent<CCamera>();
		const auto camera = m_pMainCamera->GetComponent<CCamera>();

		result = true;
	} while (false);

	return result;
}

bool CScene::Release()
{
	bool result = false;
	do {
		for (auto gameObject : m_gameObjectList)
		{
			CGameObject::Destroy(gameObject);
		}
		SAFE_DELETE(m_pMainCamera);

		result = true;
	} while (false);

	return result;
}

std::set<CGameObject*> CScene::GetListGameObject() const
{
	return m_gameObjectList;
}

std::set<CGameObject*> CScene::GetListColliderObject() const
{
	return m_colliderObjectList;
}

CScene* CScene::Instantiate()
{
	CScene* scene = nullptr;
	SAFE_ALLOC(scene, CScene);

	if (!scene->Init())
		SAFE_DELETE(scene);

	return scene;
}

bool CScene::Destroy(CScene* scene)
{
	auto result = scene->Release();
	SAFE_DELETE(scene);

	return result;
}

void CScene::Update(DWORD dt)
{
	CInput::GetInstance()->Update();

	for (CGameObject* pGameObject : m_gameObjectList)
	{
		pGameObject->Update(dt);
	}

	m_pMainCamera->Update(dt);
	CGraphic::GetInstance()->SetTransform(m_pMainCamera->GetComponent<CCamera>()->GetOrthographicMatrix(),
		m_pMainCamera->GetComponent<CCamera>()->GetIdentityMatrix(),
		m_pMainCamera->GetComponent<CCamera>()->GetViewMatrix());
}

void CScene::Render()
{
}

void CScene::AddGameObject(CGameObject* gameObject)
{
	m_gameObjectList.insert(gameObject);
	gameObject->SetScene(this);
	AddColliderObject(gameObject);
}

void CScene::AddGameObjects(int amount, CGameObject* gameObject, ...)
{
	va_list args;
	va_start(args, amount);
	while (amount > 0) {
		gameObject = va_arg(args, CGameObject*);
		AddGameObject(gameObject);
		amount--;
	}
	va_end(args);
}

void CScene::AddColliderObject(CGameObject* gameObject)
{
	if (gameObject->GetComponent<CCollider>())
	{
		m_colliderObjectList.insert(gameObject);
	}
}
