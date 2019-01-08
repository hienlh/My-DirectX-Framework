#pragma once
#include "MonoBehavier.h"

class CanAttacked;

class CanBeAttacked : public Framework::CMonoBehavior
{
private:
	int m_maxHealth = 1;
	int m_health = 1;

public:
	explicit CanBeAttacked(Framework::CGameObject* gameObject) : CMonoBehavior(gameObject) {}
	CanBeAttacked(const CanBeAttacked& object);
	CanBeAttacked* Clone() override { return new CanBeAttacked(*this); }
	virtual ~CanBeAttacked() = default;

public:
	void BeAttacked(const CanAttacked *damage);
	void Heal(const unsigned int &health);

public:
	int GetCurrentHealth() const { return m_health; }
	int GetMaxHealth() const { return m_maxHealth; }
	bool IsAlive() const { return m_health > 0; }

	void InitHealth(const int &health);
	void InitMaxHealth(const int &maxHealth);

	void Update(const DWORD &dt) override {}
	void Render() override {}
};
