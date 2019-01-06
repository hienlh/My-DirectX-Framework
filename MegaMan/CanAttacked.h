#pragma once
#include "MonoBehavier.h"

class CanBeAttacked;

class CanAttacked : public Framework::CMonoBehavior
{
private:
	int m_damage = 0;

public:
	explicit CanAttacked(Framework::CGameObject *gameObject) : CMonoBehavior(gameObject) {}
	CanAttacked(const CanAttacked& object);
	CanAttacked* Clone() override { return new CanAttacked(*this); }
	~CanAttacked() = default;

public:
	void Attack(CanBeAttacked* beAttacked) const;

public:
	int GetDamage() const { return m_damage; }

	void InitDamage(const int &damage) { m_damage = damage; }

	void OnCollisionEnter(Framework::CCollision* collision) override;
	void OnTriggerEnter(Framework::CCollision* collision) override;
};
