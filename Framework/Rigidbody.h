#pragma once
#include "Component.h"

class CRigidbody : public Framework::CComponent
{ 
private:
	Vector2 _velocity;
	float _gravityScale;
	bool _isKinematic;
	float _mass;

public:
	CRigidbody(Framework::CGameObject* gameObject);
	~CRigidbody() = default;


	// Getter / Setter
public:
	inline Vector2 GetVelocity() { return _velocity; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
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
};
