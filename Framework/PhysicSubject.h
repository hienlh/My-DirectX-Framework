#pragma once
#include "Subject.h"

namespace Framework
{
	class CCollision;

	class CPhysicSubject : public CSubject
	{
	public:
		CPhysicSubject() = default;
		CPhysicSubject(const CPhysicSubject& ps) = default;
		~CPhysicSubject() override = default;

		//Method
	public:
		virtual void NotifyCollisionEnter(CCollision* collision) {}
		virtual void NotifyCollisionExit(CCollision* collision) {}
		virtual void NotifyCollisionStay(CCollision* collision) {}
		virtual void NotifyTriggerEnter(CCollision* collision) {}
		virtual void NotifyTriggerExit(CCollision* collision) {}
		virtual void NotifyTriggerStay(CCollision* collision) {}
	};
}
