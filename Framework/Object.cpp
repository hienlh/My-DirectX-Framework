#include "stdafx.h"
#include "Object.h"
#include "GameObject.h"

bool Framework::CObject::GetIsActive()
{
	return m_isActive;
}

Framework::CObject::CObject(const CObject& object)
{
	m_Name = object.m_Name + " Clone";
	m_isActive = object.m_isActive;
}

Framework::CObject& Framework::CObject::operator=(const CObject& object)
{
	m_isActive = object.m_isActive;
	return *this;
}

void Framework::CObject::CopyValue(const CObject* object)
{
	m_isActive = object->m_isActive;
}
