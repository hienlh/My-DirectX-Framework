#pragma once
#include "Object.h"

namespace Framework {
	class CGameObject;

	class CQuadTree final : public CObject
	{
	private:
		int m_id;

		int m_level;

		std::list < CGameObject* > m_pObjects = {};

		Rect m_bounds = { 0,0,1000,1000 };

		CQuadTree* m_pNodes[4] = {};

	public:
		CQuadTree(Vector2 size = { 1000,1000 });
		CQuadTree(int id, int level, Rect bounds);
		~CQuadTree() = default;

		//Override
	public:
		void Update(DWORD dt) override;

		void Render() override;

	private:
		CObject* Clone() const override { return nullptr; }

		//Method
	public:
		void clearDynamicObject();

		void split();

		int getQuadrant(Rect rectangle) const;

		tinyxml2::XMLElement* ToXmlElement(tinyxml2::XMLDocument &doc) const;

		void SaveToXml(const char* xmlPath);

		void LoadFromXml(tinyxml2::XMLElement *node);

		/**
		 * \brief Get id of the smallest sub node consist of this rectangle 
		 * \param rectangle 
		 * \return Id of QuadTree
		 */
		int getFitId(Rect rectangle) const;

		void insert(CGameObject *gameObject);

		std::list <CGameObject*> query(Rect rectangle);
	};
}
