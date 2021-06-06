#include "CanAttacked.h"
#include "CanBeAttacked.h"

CanAttacked::CanAttacked(const CanAttacked& object) : CMonoBehavior(object)
{
	m_damage = object.m_damage;
	m_targetName = object.m_targetName;
}

CanAttacked& CanAttacked::operator=(const CComponent& component)
{
	(*this).CMonoBehavior::operator=(component);

	if(const auto pCanA = dynamic_cast<const CanAttacked*>(&component))
	{
		m_damage = pCanA->m_damage;
		m_targetName = pCanA->m_targetName;
	}

	return *this;
}

void CanAttacked::Attack(CanBeAttacked* beAttacked) const
{
	beAttacked->BeAttacked(this);
}

CanAttacked* CanAttacked::AddTargetName(const std::string& name)
{
	m_targetName.push_back(name);
	return this;
}

void CanAttacked::OnCollisionEnter(Framework::CCollision* collision)
{
	CheckCanAttack(collision);
}

void CanAttacked::OnTriggerEnter(Framework::CCollision* collision)
{
	CheckCanAttack(collision);
}

void CanAttacked::CheckCanAttack(Framework::CCollision* collision)
{
	bool canAttack = false;
	if(!m_targetName.empty())
		for (auto name : m_targetName)
		{
			if (strstr(collision->GetOtherCollider()->GetName().c_str(), name.c_str()))
			{
				canAttack = true;
				break;
			}
		}
	else
		canAttack = true;

	if (canAttack)
		if (const auto canBeAttacked = collision->GetOtherCollider()->GetComponent<CanBeAttacked>())
		{
			Attack(canBeAttacked);
		}
}
