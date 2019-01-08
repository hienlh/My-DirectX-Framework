#include "ScrollController.h"

void ScrollController::Start()
{
	collider = m_pGameObject->GetComponent<Framework::CBoxCollider>();
}

void ScrollController::Update(const DWORD& dt)
{
	auto bound = collider->GetBoundGlobal();
	for (auto object : m_targets)
	{
		auto objectBound = object->GetComponent<Framework::CBoxCollider>()->GetBoundGlobal();
		if(!bound.intersect(objectBound))
		{
			RemoveTarget(object);
		}else
		{
			int tmp = m_moveLeft ? -1 : 1;
			object->GetComponent<Framework::CTransform>()->Translate(Vector2(0.05, 0) * dt * tmp);
		}
	}
}

void ScrollController::OnTriggerEnter(Framework::CCollision* collision)
{
	AddTarget(collision->GetOtherCollider());
}

void ScrollController::AddTarget(Framework::CGameObject* gameObject)
{
	m_targets.insert(gameObject);
}

void ScrollController::RemoveTarget(Framework::CGameObject* gameObject)
{
	m_targets.erase(gameObject);
}
