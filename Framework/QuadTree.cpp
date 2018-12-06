#include "stdafx.h"
#include "QuadTree.h"
#include "Graphic.h"

using namespace Framework;

CQuadTree::CQuadTree(int id, int level, Rect bounds)
{
	m_id = id;
	m_level = level;
	m_bounds = bounds;
}

void CQuadTree::Update(DWORD dt)
{
}

void CQuadTree::Render()
{
	CGraphic::GetInstance()->DrawRectangle(m_bounds, D3DCOLOR_XRGB(255, 0, 0));
	if (m_pNodes[0])
		for (CQuadTree* node : m_pNodes)
		{
			node->Render();
		}
}

void CQuadTree::clear()
{
	m_pObjects.clear();

	if (m_pNodes[0])
		for (int i = 0; i < 4; i++)
		{
			m_pNodes[i]->clear();
			SAFE_FREE(m_pNodes[i]);
		}
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

int CQuadTree::getQuadrant(Rect rectangle) const
{
	int index = -1;
	const float verticalMidpoint = m_bounds.left + static_cast<float>(m_bounds.Size().x / 2);
	const float horizontalMidpoint = m_bounds.top + static_cast<float>(m_bounds.Size().y / 2);

	const bool topQuadrant = rectangle.bottom < horizontalMidpoint;
	const bool bottomQuadrant = rectangle.top > horizontalMidpoint;

	if (rectangle.right < verticalMidpoint) {
		if (topQuadrant) index = 1;
		else if (bottomQuadrant) index = 2;
	}
	else if (rectangle.left > verticalMidpoint)
	{
		if (topQuadrant) index = 0;
		else if (bottomQuadrant) index = 3;
	}

	return index;
}

int CQuadTree::getFitId(Rect rectangle) const
{
	int id = m_id;

	// If this node is split 
	if (m_pNodes[0])
	{
		// If having a appropriate quadrant for this rectangle
		const int index = getQuadrant(rectangle);
		if (index != -1)
		{
			id = m_pNodes[index]->getFitId(rectangle);
		}
	}

	// Else this node does not have sub node or no sub node can fit with this rectangle
	return id;
}

void CQuadTree::insert(CGameObject *gameObject)
{
	//Get bound of Game Object
	const Rect bound = gameObject->GetComponent<CCollider>()->GetBoundGlobal();

	// Check if this node has sub node, get quadrant and recursive insert game object 
	// into appropriate sub node, then break out of this function
	if (m_pNodes[0])
	{
		const int index = getQuadrant(bound);
		if (index != -1)
		{
			m_pNodes[index]->insert(gameObject);
			return;
		}
	}

	// Add game object to list object of this node
	m_pObjects.push_back(gameObject);

	// Check if node has more than max objects and level lower than max level, 
	// split this node and add to appropriate sub node
	if (m_pObjects.size() > MAX_OBJECTS && m_level < MAX_LEVEL)
	{
		if (!m_pNodes[0])
		{
			split();
		}

		// To store game object to remove after that
		std::list<CGameObject*> removedObjects = {};

		for (CGameObject* object : m_pObjects)
		{
			const int index = getQuadrant(object->GetComponent<CCollider>()->GetBoundGlobal());
			if (index != -1)
			{
				m_pNodes[index]->insert(object);
				removedObjects.push_back(object);
			}
		}
		for (CGameObject* object : removedObjects)
		{
			m_pObjects.remove(object);
		}
	}
}

std::list<CGameObject*> CQuadTree::query(Rect rectangle)
{
	std::list<CGameObject*> result = {};

	// Check if it overlap with this node, then get all objects of this node to result;
	if (!m_bounds.intersect(rectangle))
		return result;

	for (CGameObject* object : m_pObjects)
	{
		result.push_back(object);
	}

	//Check if this node is split, get all objects of sub node intersecting with this rectangle
	const int index = getQuadrant(rectangle);
	if (index != -1 && m_pNodes[0]) // If this rectangle is cover by 1 sub node, just get objects of this node
	{
		auto tmp = m_pNodes[index]->query(rectangle);
		for (CGameObject* object : tmp)
		{
			result.push_back(object);
		}
	}
	else if (m_pNodes[0])// Else check all of sub node
	{
		for (CQuadTree* node : m_pNodes)
		{
			auto tmp = node->query(rectangle);
			for (CGameObject* object : tmp)
			{
				result.push_back(object);
			}
		}
	}

	return result;
}
