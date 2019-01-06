#include "CanBeAttacked.h"
#include "GameManager.h"
#include "CanAttacked.h"

CanBeAttacked::CanBeAttacked(const CanBeAttacked& object) : CMonoBehavior(object)
{
	m_alive = object.m_alive;
	m_health = object.m_health;
	m_maxHealth = object.m_maxHealth;
}

void CanBeAttacked::BeAttacked(const CanAttacked *damage)
{
	m_health -= damage->GetDamage();
	if (m_health < 0) {
		m_health = 0;
		m_alive = false;
	}
	//CDebug::Log("CanBeAttacked.cpp:12 - Be Attacked (Current Health: %d)\n", m_health);
}

void CanBeAttacked::Heal(const unsigned int& health)
{
	m_health += health;
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
}

/**
 * \brief Can not use when the game is running
 * \param health If larger than Max Health, auto init Max health equal this
 */
void CanBeAttacked::InitHealth(const int& health)
{
	if (Framework::CGameManager::GetInstance()->IsRunning()) return;

	m_health = health;
	if (m_health > m_maxHealth)
		InitMaxHealth(m_health);
}

/**
 * \brief Can not use when the game is running
 * \param maxHealth If smaller than Current Health, auto init current health equal this
 */
void CanBeAttacked::InitMaxHealth(const int& maxHealth)
{
	if (Framework::CGameManager::GetInstance()->IsRunning()) return;

	m_maxHealth = maxHealth;
	if (m_maxHealth < m_health)
		InitHealth(m_maxHealth);
}
