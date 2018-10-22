#include "Scene.h"
#include "Graphic.h"
#include <string>
#include "Camera.h"
#include "Collider.h"

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
		m_mainCamera = CGameObject::Instantiate(String("Main Camera"), Vector2(0, 0));
		m_mainCamera->AddComponent<CCamera>();
		const auto camera = m_mainCamera->GetComponent<CCamera>();

		result = true;
	} while (false);

	return result;
}

bool CScene::Release()
{
	do {
		for (auto gameObject : m_listGameObject)
		{
			CGameObject::Destroy(gameObject);
		}
		SAFE_DELETE(m_mainCamera);
	} while (false);

	return true;
}

std::set<CGameObject*> CScene::GetListGameObject() const
{
	return m_listGameObject;
}

std::set<CGameObject*> CScene::GetListColliderObject() const
{
	return m_listColliderObject;
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
	for (auto gameOnject : m_listGameObject)
	{
		gameOnject->Update(dt);
	}

	m_mainCamera->Update(dt);
	CGraphic::GetInstance()->SetTransform(m_mainCamera->GetComponent<CCamera>()->GetOrthographicMatrix(),
	                                      m_mainCamera->GetComponent<CCamera>()->GetIdentityMatrix(),
	                                      m_mainCamera->GetComponent<CCamera>()->GetViewMatrix());
}

void CScene::Render()
{
	CGraphic::GetInstance()->Render(m_listGameObject);
}

void CScene::AddGameObject(CGameObject* gameObject)
{
	m_listGameObject.insert(gameObject);
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
	if(gameObject->GetComponent<CCollider>())
	{
		m_listColliderObject.insert(gameObject);
	}
}
