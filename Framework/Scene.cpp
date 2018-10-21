#include "Scene.h"
#include "Graphic.h"
#include <string>
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
		m_mainCamera = CGameObject::Instantiate(Vector2(0, 0));
		m_mainCamera->AddComponent<CCamera>();
		const auto camera = m_mainCamera->GetComponent<CCamera>();

		result = true;
	} while (false);

	return result;
}

bool CScene::Release()
{
	do {
		for (auto gameObject : _listGameObject)
		{
			CGameObject::Destroy(gameObject);
		}
		SAFE_DELETE(m_mainCamera);
	} while (false);

	return true;
}

std::vector<CGameObject*> CScene::GetListGameObject()
{
	return _listGameObject;
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
	for (auto gameOnject : _listGameObject)
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
	CGraphic::GetInstance()->Render(_listGameObject);
}

void CScene::AddGameObject(CGameObject* gameObject)
{
	_listGameObject.push_back(gameObject);
}