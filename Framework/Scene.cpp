#include "stdafx.h"
#include "Scene.h"
#include "GameManager.h"
#include "Camera.h"

using namespace Framework;

bool CScene::Init()
{
	InitMainCamera();
	m_pQuadTree = new CQuadTree(0, 0, Rect(0, 0, 600, 600));
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
	const auto result = scene->Release();
	SAFE_DELETE(scene);

	return result;
}

void CScene::Update(DWORD dt)
{
	CInput::GetInstance()->Update();

	m_pQuadTree->clear();
	for (CGameObject* const object : m_colliderObjectList)
	{
		m_pQuadTree->insert(object);
	}

	for (CGameObject* pGameObject : m_gameObjectList)
	{
		pGameObject->Update(dt);

		if (pGameObject->GetName() == L"Player")
		{
			auto tmp = m_pQuadTree->query(pGameObject->GetComponent<CCollider>()->GetBoundGlobal());
		}
	}

	m_pMainCamera->Update(dt);
	CGraphic::GetInstance()->SetTransform(m_pMainCamera->GetComponent<CCamera>()->GetOrthographicMatrix(),
		m_pMainCamera->GetComponent<CCamera>()->GetIdentityMatrix(),
		m_pMainCamera->GetComponent<CCamera>()->GetViewMatrix());
}

void CScene::Render()
{
	std::set<CGameObject*> listRender = m_gameObjectList;
	listRender.insert(reinterpret_cast<CGameObject*>(m_pQuadTree));
	CGraphic::GetInstance()->Render(listRender);
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
