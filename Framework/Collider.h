#pragma once
#include "Component.h"
#include "Bound.h"

namespace Framework {

	class CCollider : public CComponent
	{
		//Properties
	protected:
		Vector2 m_Offset;
		Vector2 m_Anchor;
		Bound m_Bound;
		bool m_IsTrigger;
		bool m_UsedByEffector;
		bool m_IsDebugging;
		bool m_AutoBoundSize; //Used when animator have a lot of different sizes

		//Cons / Des
	public:
		CCollider(CGameObject* gameObject);
		virtual ~CCollider() = default;

		//Getter / Setter
	public:
		Bound GetBoundGlobal() const;
		bool GetUsedByEffector() const;
		bool GetIsDebugging() const;
		bool GetAutoBoundSize() const;
		Vector2 GetAnchor() const;

		void SetUsedByEffector(bool usedByEffector);
		/*void SetBoundSize(Vector2 size);*/
		void SetOffset(Vector2 offset);
		void SetIsDebugging(bool isDebugging);
		void SetAutoBoundSize(bool autoBoundSize);
		void SetAnchor(Vector2 anchor);
	};
}