#pragma once
#include "Collider.h"

namespace Framework {

	class CBoxCollider : public CCollider
	{
	private:
		Vector2 m_Size;
	public:
		CBoxCollider(CGameObject* gameObject);
		~CBoxCollider() = default;

		void Config(bool isTrigger = false, bool autoBoundSize = false, bool usedByEffector = true, bool isDebugging = false);

		//Getter / Setter
	public:
		Vector2 GetSize() const { return m_Size; }

		void SetSize(Vector2 size);

		//Override
	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}