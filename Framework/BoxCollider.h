#pragma once
#include "Collider.h"

namespace Framework {

	class CBoxCollider : public CCollider
	{
	private:
		Vector2 m_Size = VECTOR2_ZERO;
	public:
		CBoxCollider(const CBoxCollider &boxCollider);
		explicit CBoxCollider(CGameObject* gameObject);
		~CBoxCollider() = default;

		//Getter / Setter
	public:
		const Vector2& GetSize() const { return m_Size; }

		CBoxCollider* SetSize(const Vector2 &size);
		CBoxCollider* PlusSize(const Vector2 &size);

		//Override
	public:
		void Update(const DWORD &dt) override;
		void Render() override;
		CBoxCollider* Clone() override { return new CBoxCollider(*this); }
		CBoxCollider& operator=(const CComponent& component) override;
	};
}