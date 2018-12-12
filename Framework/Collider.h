#pragma once
#include "Component.h"
#include "Bound.h"

namespace Framework {

	class CCollider : public CComponent
	{
		//Properties
	protected:
		Vector2 m_Offset = VECTOR2_ZERO;
		Vector2 m_Anchor = VECTOR2_ONE;
		Bound m_Bound = {};
		bool m_IsTrigger = false;
		bool m_UsedByEffector = true;
		bool m_IsDebugging = false;
		bool m_AutoBoundSize = false; //Used when animator have a lot of different sizes

		//Cons / Des
	public:
		CCollider(const CCollider& collider);
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

	public:
		virtual CCollider* Clone() const override = 0;
	};
}