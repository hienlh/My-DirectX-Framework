#pragma once
#include "Component.h"
#include "Bound.h"

namespace Framework {

	class CCollider : public CComponent
	{
		//Properties
	protected:
		Vector2 m_Offset = VECTOR2_ZERO;
		Vector2 m_Anchor = {0.5, 0.5};
		Bound m_Bound = {};
		bool m_IsTrigger = false;
		bool m_UsedByEffector = true;
		bool m_AutoBoundSize = false; //Used when animator have a lot of different sizes

		//Cons / Des
	public:
		CCollider(const CCollider& collider);
		explicit CCollider(CGameObject* gameObject) : CComponent(gameObject){}
		virtual ~CCollider() = default;

		//Getter / Setter
	public:
		Bound GetBoundGlobal() const;
		Rect GetBoundArea() const;
		const bool &GetUsedByEffector() const;
		const bool& GetAutoBoundSize() const;
		const bool& GetIsTrigger() const;
		Vector2 GetAnchor() const;

		void SetUsedByEffector(const bool &usedByEffector);
		/*void SetBoundSize(Vector2 size);*/
		void SetOffset(const Vector2 &offset);
		void SetAutoBoundSize(const bool &autoBoundSize);
		void SetAnchor(const Vector2& anchor);
		void SetIsTrigger(const bool &isTrigger);

	public:
		void Update(const DWORD &dt) override = 0;
		void Render() override = 0;
		CCollider* Clone() override = 0;
		CCollider& operator=(const CComponent& component) override;
	};
}