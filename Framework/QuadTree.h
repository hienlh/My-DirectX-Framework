#pragma once
#include "stdafx.h"
#include "Object.h"

namespace Framework {
	class CGameObject;

	class CQuadTree final : public CObject
	{
	private:
		int m_id;

		int m_level;

		std::list < CGameObject* > m_pObjects = {};

		Rect m_bounds = {};

		CQuadTree* m_pNodes[4] = {};

	public:
		CQuadTree(int id, int level, Rect bounds);
		~CQuadTree() = default;

		//Override
	public:
		void Update(DWORD dt) override;

		void Render() override;

		//Method
	public:
		void clear();

		void split();

		int getQuadrant(Rect rectangle) const;

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
