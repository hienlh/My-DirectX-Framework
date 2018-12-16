#include "stdafx.h"
#include "Object.h"

Framework::CObject::CObject(const CObject& object)
{
	m_Name = object.m_Name + " Clone";
	m_isActive = object.m_isActive;
}
