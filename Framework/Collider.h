#pragma once
#include "Component.h"
#include "Bounds.h"

using namespace Framework;

class CCollider : public CComponent
{
	//Properties
protected:
	Vector2 m_Offset;
	Bounds m_Bound;
	bool m_IsTrigger;
	bool m_UsedByEffector;

	//Cons / Des
public:
	CCollider(CGameObject* gameObject);
	virtual ~CCollider() = default;

	//Getter / Setter
public:
	Bounds GetBoundGlobal() const;
	bool GetUsedByEffector() const;

	void SetUsedByEffector(bool usedByEffector);
	void SetBoundSize(Vector2 size);
	void SetOffet(Vector2 offset);
};
