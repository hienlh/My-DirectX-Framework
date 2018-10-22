#pragma once
#include "Component.h"
#include "Bounds.h"

using namespace Framework;

class CCollider : public CComponent
{
	//Properties
protected:
	Vector2 m_offset;
	Bounds m_bounds;
	bool m_isTrigger;
	bool m_usedByEffector;

	//Cons / Des
public:
	CCollider(CGameObject* gameObject);
	virtual ~CCollider() = default;

	//Getter / Setter
public:
	Bounds GetBounds() const;
	bool GetUsedByEffector() const;

	void SetUsedByEffector(bool usedByEffector) { m_usedByEffector = usedByEffector; }
};
