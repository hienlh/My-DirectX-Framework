#pragma once
#include "Component.h"

namespace Framework {

	class CRigidbody : public CComponent
	{
	private:
		Vector2 m_velocity = VECTOR2_ZERO;
		float m_gravityScale = 1;
		bool m_isKinematic = false;
		float m_mass = 0;
		Rect m_limitedArea = { 0,0,0,0 };

	public:
		CRigidbody(const CRigidbody &rigidbody);
		CRigidbody(CGameObject* gameObject);
		~CRigidbody() = default;


		// Getter / Setter
	public:
		inline Vector2 GetVelocity() const { return m_velocity; }
		float GetGravityScale() const { return m_gravityScale; }
		float GetMass() const { return m_mass; }
		bool GetIsKinematic() const { return m_isKinematic; }
		Rect GetLimitedArea() const { return m_limitedArea; }

		CRigidbody* SetVelocity(Vector2 velocity) { SetVelocity(velocity.x, velocity.y); return this; }
		CRigidbody* SetVelocity(float x = MAX_VELOCITY, float y = MAX_VELOCITY);
		CRigidbody* AddVelocity(Vector2 velocity) { m_velocity += velocity; return this; }
		CRigidbody* SetMass(float mass) { m_mass = mass; return this; }
		CRigidbody* SetIsKinematic(bool isKinematic);
		CRigidbody* SetGravityScale(float gravityScale) { m_gravityScale = gravityScale; return this; }
		CRigidbody* SetLimitedArea(Rect limitedArea);

		// Override
	public:
		void Update(DWORD dt) override;
		void Render() override;

		CRigidbody* Clone() const override;
		
		//Friend
	public:
		friend class CPhysic;
	};
}