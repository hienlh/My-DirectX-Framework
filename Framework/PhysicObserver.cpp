#include "stdafx.h"
#include "PhysicObserver.h"
#include "Physic.h"

Framework::CPhysicObserver::CPhysicObserver() : CObserver(CPhysic::GetInstance())
{
}
