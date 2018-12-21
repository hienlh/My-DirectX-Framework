#include "stdafx.h"
#include "PhysicObserver.h"
#include "Physic.h"

Framework::CPhysicObserver::CPhysicObserver()
{
	CPhysic::GetInstance()->RegisterObserver(this);
}

Framework::CPhysicObserver::~CPhysicObserver()
{
	CPhysic::GetInstance()->RemoveObserver(this);
}
