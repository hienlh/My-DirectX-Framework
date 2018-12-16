#pragma once
#include "Object.h"

namespace Framework {
	class CGameObject;

	class CQuadTree final : public CObject
	{
	private:
		int m_id;

		int m_level;

		std::set < CGameObject* > m_pObjects = {};

		Rect m_bounds = { 0,0,1000,1000 };

		CQuadTree* m_pNodes[4] = {};

	public:
		CQuadTree(Vector2 size = { 1000,1000 });
		CQuadTree(int id, int level, Rect bounds);
		~CQuadTree();

		//Override
	public:
		void Update(DWORD dt) override;

		void Render() override;

	private:
		CObject* Clone() const override { return nullptr; }

		//Method
	public:

		static int GetAmountGameObjects(CQuadTree* quadTree);

		void split();

		void remove(CGameObject* gameObject);

		tinyxml2::XMLElement* ToXmlElement(tinyxml2::XMLDocument &doc) const;

		void SaveToXml(const char* xmlPath) const;

		void LoadFromXml(tinyxml2::XMLElement *node);

		void insert(CGameObject *gameObject);

		void insert_s(CGameObject *gameObject);

		std::set <CGameObject*> query(Rect rectangle);
	};
}
