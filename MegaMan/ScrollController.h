#pragma once
#include "MonoBehavier.h"

class ScrollController : public Framework::CMonoBehavior
{
private:
	bool m_moveLeft = false;
	std::set<Framework::CGameObject*> m_targets = {};

	Framework::CBoxCollider* collider = nullptr;


public:
	ScrollController(const ScrollController& monoBehavior)
		: CMonoBehavior(monoBehavior)
	{
	}

	explicit ScrollController(Framework::CGameObject* gameObject)
		: CMonoBehavior(gameObject)
	{
	}

	ScrollController& operator=(const CComponent& component) override
	{
		(*this).CMonoBehavior::operator=(component);

		if (const auto pMet = dynamic_cast<const ScrollController*>(&component))
		{
		}

		return *this;
	}

	CMonoBehavior* Clone() override { return new ScrollController(*this); }

	void Start() override;
	void Update(const DWORD& dt) override;
	void OnTriggerEnter(Framework::CCollision* collision) override;

	ScrollController* SetMoveLeft(const bool& moveLeft = true) { m_moveLeft = moveLeft; return this; }

private:
	void AddTarget(Framework::CGameObject* gameObject);
	void RemoveTarget(Framework::CGameObject* gameObject);

};
