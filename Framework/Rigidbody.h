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
		Vector2 GetVelocity()		const { return _velocity; }
		float	GetGravityScale()	const { return _gravityScale; }
		float	GetMass()			const { return _mass; }
		bool	GetIsKinematic()	const { return _isKinematic; }

		void SetVelocity(Vector2 velocity) { _velocity = velocity; }
		void SetGravityScale(float gravityScale) { _gravityScale = gravityScale; }
		void SetMass(float mass) { _mass = mass; }
		void SetIsKinematic(bool isKinematic) { _isKinematic = isKinematic; }

		// Override
	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}