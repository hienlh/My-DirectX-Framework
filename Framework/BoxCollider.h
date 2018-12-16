#pragma once
#include "Collider.h"

namespace Framework {

	class CBoxCollider : public CCollider
	{
	private:
		Vector2 m_Size = VECTOR2_ZERO;
	public:
		CBoxCollider(const CBoxCollider &boxCollider);
		CBoxCollider(CGameObject* gameObject);
		~CBoxCollider() = default;

		//Getter / Setter
	public:
		Vector2 GetSize() const { return m_Size; }

		CBoxCollider* SetSize(Vector2 size);
		CBoxCollider* PlusSize(Vector2 size);

		//Override
	public:
		void Update(DWORD dt) override;
		void Render() override;

		CBoxCollider* Clone() const override;
	};
}