#include "stdafx.h"
#include "Scene.h"
#include "GameManager.h"
#include "Camera.h"
#include "Rigidbody.h"

using namespace Framework;

CScene::CScene(std::string name, Vector2 quadTreeSize)
{
	if (!this->Init(name, quadTreeSize))
		delete this;
}

bool CScene::Init(std::string name, Vector2 quadTreeSize)
{
	if (!InitMainCamera()) return false;

	struct stat buffer;
	if(stat("QuadTree.xml", &buffer) == 0)
	{
		m_loadedQuadTree = true;
	}

	m_pQuadTree = new CQuadTree(quadTreeSize);
	m_Name = name;

	return true;
}

bool CScene::InitMainCamera()
{
	bool result = false;
	do
	{
		m_pMainCamera = new CGameObject("Main Camera");
		m_pMainCamera->AddComponent<CCamera>();

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

bool CScene::Destroy(CScene* scene)
{
	const auto result = scene->Release();
	SAFE_DELETE(scene);

	return result;
}

void CScene::Update(DWORD dt)
{
	CInput::GetInstance()->Update();

	// Remove dynamic gameObjects
	m_pQuadTree->clearDynamicObject();
	// ReAdd dynamic gameObjects
	for (CGameObject* const object : m_colliderObjectList)
	{
		if(!object->GetComponent<CRigidbody>()->GetIsKinematic())
			m_pQuadTree->insert(object);
	}

	for (CGameObject* pGameObject : m_gameObjectList)
	{
		pGameObject->Update(dt);

		if (pGameObject->GetName() == "Player")
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

bool CScene::AddGameObject(CGameObject* gameObject)
{
	/*const auto name = gameObject->GetName();
	if (FindGameObject(name))
	{
		return false;
	}*/

	m_gameObjectList.insert(gameObject);
	gameObject->SetScene(this);
	AddColliderObject(gameObject);
	return true;
}

CGameObject* CScene::FindGameObject(std::string name)
{
	for (CGameObject* const game_object : m_gameObjectList)
	{
		if (game_object->GetName() == name)
			return game_object;
	}

	return nullptr;
}

CGameObject* CScene::FindGameObject(DWORD id)
{
	for (CGameObject* const game_object : m_gameObjectList)
	{
		if (game_object->GetID() == id)
			return game_object;
	}

	return nullptr;
}

void CScene::AddColliderObject(CGameObject* gameObject)
{
	if (gameObject->GetComponent<CCollider>())
	{
		m_colliderObjectList.insert(gameObject);

		if (!m_loadedQuadTree && gameObject->GetComponent<CRigidbody>()->GetIsKinematic())
			m_pQuadTree->insert(gameObject);
	}
}

void CScene::SaveQuadTree() const
{
	m_pQuadTree->clearDynamicObject();
	m_pQuadTree->SaveToXml("QuadTree.xml");
}

void CScene::LoadQuadTree() const
{
	if (m_loadedQuadTree) 
	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile("QuadTree.xml") == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLNode* pRoot = doc.FirstChild();

			tinyxml2::XMLElement * pNodeRoot = pRoot->FirstChildElement("Node");

			m_pQuadTree->LoadFromXml(pNodeRoot);
		}
	}
	else SaveQuadTree();
}
