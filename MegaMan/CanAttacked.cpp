#include "CanAttacked.h"
#include "CanBeAttacked.h"

CanAttacked::CanAttacked(const CanAttacked& object) : CMonoBehavior(object)
{
	m_damage = object.m_damage;
}

void CanAttacked::Attack(CanBeAttacked* beAttacked) const
{
	beAttacked->BeAttacked(this);
}

void CanAttacked::OnCollisionEnter(Framework::CCollision* collision)
{
	if(const auto canBeAttacked = collision->GetOtherCollider()->GetComponent<CanBeAttacked>())
	{
		Attack(canBeAttacked);
	}
}

void CanAttacked::OnTriggerEnter(Framework::CCollision* collision)
{
	if (const auto canBeAttacked = collision->GetOtherCollider()->GetComponent<CanBeAttacked>())
	{
		Attack(canBeAttacked);
	}
}
