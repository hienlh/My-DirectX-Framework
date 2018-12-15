#include "stdafx.h"
#include "QuadTree.h"
#include "Graphic.h"
#include "Rigidbody.h"
#include "GameManager.h"
#include "Collider.h"

using namespace Framework;

CQuadTree::CQuadTree(Vector2 size)
{
	m_id = 0;
	m_level = 0;
	m_bounds = Rect(Vector2(0,0), size);
}

CQuadTree::CQuadTree(int id, int level, Rect bounds)
{
	m_id = id;
	m_level = level;
	m_bounds = bounds;
}

CQuadTree::~CQuadTree()
{
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(m_pNodes[i]);
}

void CQuadTree::Update(DWORD dt)
{
}

void CQuadTree::Render()
{
	CGraphic::GetInstance()->DrawRectangle(m_bounds, D3DCOLOR_XRGB(255, 0, 0));
	if(m_pNodes[0])
		for (CQuadTree* node : m_pNodes)
		{
			node->Render();
		}
}

int CQuadTree::GetAmountGameObjects(CQuadTree* quadTree)
{
	int result = 0;
	if(quadTree->m_pNodes[0])
	{
		for (CQuadTree* node : quadTree->m_pNodes)
		{
			result += GetAmountGameObjects(node);
		}
	}
	else
	{
		result += quadTree->m_pObjects.size();
	}

	return result;
}

void CQuadTree::split()
{
	const int subWidth = m_bounds.Size().x / 2;
	const int subHeight = m_bounds.Size().y / 2;
	const int x = m_bounds.left;
	const int y = m_bounds.top;

	m_pNodes[0] = new CQuadTree(m_id * 10 + 1, m_level + 1, Rect(Vector2(x + subWidth, y), Vector2(subWidth, subHeight)));
	m_pNodes[1] = new CQuadTree(m_id * 10 + 2, m_level + 1, Rect(Vector2(x, y), Vector2(subWidth, subHeight)));
	m_pNodes[2] = new CQuadTree(m_id * 10 + 3, m_level + 1, Rect(Vector2(x, y + subHeight), Vector2(subWidth, subHeight)));
	m_pNodes[3] = new CQuadTree(m_id * 10 + 4, m_level + 1, Rect(Vector2(x + subWidth, y + subHeight), Vector2(subWidth, subHeight)));
}

void CQuadTree::remove(CGameObject* gameObject)
{
	if (CGameManager::GetInstance()->IsRunning()) return;
	
	if(m_pNodes[0])
	{
		for (CQuadTree* node : m_pNodes)
		{
			node->remove(gameObject);
		}

		if(!GetAmountGameObjects(this))
		{
			for(int i=0;i<4;i++)
				SAFE_DELETE(m_pNodes[i]);
		}
	}
	else
	{
		m_pObjects.erase(gameObject);
	}
}

tinyxml2::XMLElement* CQuadTree::ToXmlElement(tinyxml2::XMLDocument &doc) const
{
	tinyxml2::XMLElement *result = doc.NewElement("Node");

	result->SetAttribute("id", m_id);
	result->SetAttribute("x", m_bounds.left);
	result->SetAttribute("y", m_bounds.top);
	result->SetAttribute("width", m_bounds.Size().x);
	result->SetAttribute("height", m_bounds.Size().y);

	if(m_pNodes[0])
	{
		auto pNodes = doc.NewElement("ChildNodes");
		for (CQuadTree* const node : m_pNodes)
		{
			pNodes->InsertEndChild(node->ToXmlElement(doc));
		}
		result->InsertEndChild(pNodes);
	}
	else
	{
		if (m_pObjects.size() != 0) {
			auto gameObjects = doc.NewElement("GameObjects");
			for (CGameObject* const game_object : m_pObjects)
			{
				const auto transform = game_object->GetComponent<CTransform>();
				const auto collider = game_object->GetComponent<CBoxCollider>();

				const Vector2 pos = transform->Get_Position();

				auto gameObject = doc.NewElement("GameObjectID");
				gameObject->SetAttribute("id", static_cast<int>(game_object->GetID()));
				gameObject->SetAttribute("name", game_object->GetName().c_str());
				gameObject->SetAttribute("posX", pos.x);
				gameObject->SetAttribute("posY", pos.y);

				gameObjects->InsertEndChild(gameObject);
			}
			result->InsertFirstChild(gameObjects);
		}
	}

	return result;
}

void CQuadTree::SaveToXml(const char* xmlPath) const
{
	FILE* file;
	fopen_s(&file, xmlPath, "wb");

	tinyxml2::XMLDocument doc;

	auto pRoot = doc.NewElement("QuadTree");
	doc.InsertFirstChild(pRoot);

	pRoot->InsertFirstChild(ToXmlElement(doc));

	doc.SaveFile(file);
	fclose(file);
}

void CQuadTree::LoadFromXml(tinyxml2::XMLElement *node)
{
	this->m_id = node->IntAttribute("id");
	this->m_bounds = Bound(Vector2(node->IntAttribute("y"), node->IntAttribute("x")),
	                 Vector2(node->IntAttribute("width"), node->IntAttribute("height")));

	if (auto childNodes = node->FirstChildElement("ChildNodes"))
	{
		split();
		tinyxml2::XMLElement * childNode = childNodes->FirstChildElement("Node");
		int index = 0;
		while (childNode)
		{
			m_pNodes[index++]->LoadFromXml(childNode);
			childNode = childNode->NextSiblingElement("Node");
		}

	}else
	{
		if (auto gameObjects = node->FirstChildElement("GameObjects"))
		{
			tinyxml2::XMLElement * gameObjectXML = gameObjects->FirstChildElement("GameObjectID");
			CScene *scene = CGameManager::GetInstance()->GetCurrentScene();
			while (gameObjectXML != nullptr)
			{
				auto gameObject = scene->FindGameObject(gameObjectXML->IntAttribute("id", -1));

				if (gameObject) {
					gameObject->GetComponent<CTransform>()
						->Set_Position(Vector2(gameObjectXML->IntAttribute("posX", 0), gameObjectXML->IntAttribute("posY", 0)));

					this->m_pObjects.insert(gameObject);
				}
				gameObjectXML = gameObjectXML->NextSiblingElement("GameObjectID");
			}

		}
	}
}

void CQuadTree::insert(CGameObject *gameObject)
{
	if (CGameManager::GetInstance()->IsRunning()) return;

	if(!m_pNodes[0])
	{
		if (m_level < MAX_QUAD_TREE_LEVEL) split();
		else
		{
			m_pObjects.insert(gameObject);
			return;
		}
	}

	const auto rigidBody = gameObject->GetComponent<CRigidbody>();
	for (CQuadTree* node : m_pNodes)
	{
		if (rigidBody->GetIsKinematic()) {
			if (node->m_bounds.intersect(gameObject->GetComponent<CCollider>()->GetBoundGlobal())) 
				node->insert(gameObject);
		}
		else if (rigidBody->GetLimitedArea() != Rect(0, 0, 0, 0))
		{
			if (node->m_bounds.intersect(gameObject->GetComponent<CCollider>()->GetBoundArea()))
				node->insert(gameObject);
		}
	}
}

void CQuadTree::insert_s(CGameObject* gameObject)
{
	if (CGameManager::GetInstance()->IsRunning()) return;

	remove(gameObject);

	insert(gameObject);
}

std::set<CGameObject*> CQuadTree::query(Rect rectangle)
{
	std::set<CGameObject*> result = {};

	if(m_pNodes[0])
	{
		for (CQuadTree* node : m_pNodes)
		{
			auto nodeResult = node->query(rectangle);
			result.insert(nodeResult.begin(), nodeResult.end());
		}
	}
	else
	{
		result.insert(m_pObjects.begin(), m_pObjects.end());
	}

	return result;
}
