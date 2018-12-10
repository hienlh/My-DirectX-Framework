#pragma once
#include "Component.h"

namespace Framework {

	class CRigidbody : public CComponent
	{
	private:
		Vector2 _velocity;
		float _gravityScale;
		bool _isKinematic;
		float _mass;

	public:
		CRigidbody(CGameObject* gameObject);
		~CRigidbody() = default;


		// Getter / Setter
	public:
		inline Vector2 GetVelocity() { return _velocity; }
		void SetVelocity(Vector2 velocity) { SetVelocity(velocity.x, velocity.y); }
		void SetVelocity(float x = MAX_VELOCITY, float y = MAX_VELOCITY)
		{
			if (fabs(x - MAX_VELOCITY) > EPSILON)
				_velocity.x = x;
			if (fabs(y - MAX_VELOCITY) > EPSILON)
				_velocity.y = y;
		}
		void AddVelocity(Vector2 velocity) { _velocity += velocity; }
		void MinarVelocity(Vector2 velocity) { _velocity -= velocity; }
		float GetGravityScale() { return _gravityScale; }
		void SetGravityScale(float gravityScale) { _gravityScale = gravityScale; }
		float GetMass() { return _mass; }
		void SetMass(float mass) { _mass = mass; }
		bool GetIsKinematic() { return _isKinematic; }
		void SetIsKinematic(bool isKinematic) { _isKinematic = isKinematic; }

		// Override
	public:
		void Update(DWORD dt) override;
		void Render();
		
		//Friend
	public:
		friend class CPhysic;
	};
}