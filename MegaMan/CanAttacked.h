#pragma once
#include "MonoBehavier.h"

class CanBeAttacked;

class CanAttacked : public Framework::CMonoBehavior
{
private:
	int m_damage = 0;
	std::vector<std::string> m_targetName = {};

public:
	explicit CanAttacked(Framework::CGameObject *gameObject) : CMonoBehavior(gameObject) {}
	CanAttacked(const CanAttacked& object);
	CanAttacked* Clone() override { return new CanAttacked(*this); }
	~CanAttacked() = default;
	CanAttacked& operator=(const CComponent& component) override;

public:
	void Attack(CanBeAttacked* beAttacked) const;

public:
	int GetDamage() const { return m_damage; }

	CanAttacked* AddTargetName(const std::string &name);

	CanAttacked* InitDamage(const int &damage) { m_damage = damage; return this; }

	void OnCollisionEnter(Framework::CCollision* collision) override;
	void OnTriggerEnter(Framework::CCollision* collision) override;

private:
	void CheckCanAttack(Framework::CCollision* collision);
};
