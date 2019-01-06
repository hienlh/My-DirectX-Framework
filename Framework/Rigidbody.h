#pragma once
#include "Component.h"

namespace Framework {

	class CRigidbody : public CComponent
	{
	private:
		Vector2 m_velocity = VECTOR2_ZERO;
		float m_gravityScale = 1;
		bool m_isKinematic = false;
		bool m_needUpdate = false;
		float m_mass = 0;
		Rect m_limitedArea = { 0,0,0,0 };


	public:
		CRigidbody(const CRigidbody &rigidbody);
		CRigidbody(CGameObject* gameObject) : CComponent(gameObject) { };
		~CRigidbody() = default;


		// Getter / Setter
	public:
		inline Vector2 GetVelocity() const { return m_velocity; }
		float GetGravityScale() const { return m_gravityScale; }
		float GetMass() const { return m_mass; }
		bool GetIsKinematic() const { return m_isKinematic; }
		Rect GetLimitedArea() const { return m_limitedArea; }
		bool GetNeedUpdate() const { return m_needUpdate; }

		CRigidbody* SetVelocity(const Vector2 &velocity) { SetVelocity(velocity.x, velocity.y); return this; }
		CRigidbody* SetVelocity(const float &x = MAX_VELOCITY, const float &y = MAX_VELOCITY);
		CRigidbody* AddVelocity(const Vector2 &velocity) { m_velocity += velocity; return this; }
		CRigidbody* SetMass(const float &mass) { m_mass = mass; return this; }
		CRigidbody* SetIsKinematic(const bool &isKinematic);
		CRigidbody* SetGravityScale(const float& gravityScale) { m_gravityScale = gravityScale; return this; }
		CRigidbody* SetLimitedArea(const Rect& limitedArea);
		CRigidbody* SetNeedUpdate(const bool &needUpdate) { m_needUpdate = needUpdate; return this; }

		// Override
	public:
		void Update(DWORD dt) override;
		void Render() override;
		CRigidbody* Clone() override { return new CRigidbody(*this); }
		//Friend
		friend class CPhysic;
	};
}