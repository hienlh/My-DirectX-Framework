#pragma once
#include "Component.h"
#include "Bound.h"

namespace Framework {

	class CCollider : public CComponent
	{
		//Properties
	protected:
		Vector2 m_Offset;
		Bound m_Bound;
		bool m_IsTrigger;
		bool m_UsedByEffector;
		bool m_IsDebugging;

		//Cons / Des
	public:
		CCollider(CGameObject* gameObject);
		virtual ~CCollider() = default;

		//Getter / Setter
	public:
		Bound GetBoundGlobal() const;
		bool GetUsedByEffector() const;
		bool GetIsDebugging() const;

		void SetUsedByEffector(bool usedByEffector);
		/*void SetBoundSize(Vector2 size);*/
		void SetOffset(Vector2 offset);
		void SetIsDebugging(bool isDebugging);
	};
}