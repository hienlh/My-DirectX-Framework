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

	public:
		CRigidbody(const CRigidbody &rigidbody);
		CRigidbody(CGameObject* gameObject);
		~CRigidbody() = default;


		// Getter / Setter
	public:
		inline Vector2 GetVelocity() const { return m_velocity; }
		void SetVelocity(Vector2 velocity) { SetVelocity(velocity.x, velocity.y); }
		void SetVelocity(float x = MAX_VELOCITY, float y = MAX_VELOCITY)
		{
			if (fabs(x - MAX_VELOCITY) > EPSILON) 
				m_velocity.x = x;
			if (fabs(y - MAX_VELOCITY) > EPSILON) 
				m_velocity.y = y;
		}
		void AddVelocity(Vector2 velocity) { m_velocity += velocity; }
		void MinarVelocity(Vector2 velocity) { m_velocity -= velocity; }
		float GetGravityScale() const { return m_gravityScale; }
		void SetGravityScale(float gravityScale) { m_gravityScale = gravityScale; }
		float GetMass() const { return m_mass; }
		void SetMass(float mass) { m_mass = mass; }
		bool GetIsKinematic() const { return m_isKinematic; }
		void SetIsKinematic(bool isKinematic);

		// Override
	public:
		void Update(DWORD dt) override;
		void Render();

		CRigidbody* Clone() const override;
		
		//Friend
	public:
		friend class CPhysic;
	};
}