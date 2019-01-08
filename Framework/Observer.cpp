#include "stdafx.h"
#include "Observer.h"

using namespace Framework;

CObserver::~CObserver()
{
	if(m_subject)
		m_subject->RemoveObserver(this);
}

void CObserver::AddToSubject()
{
	if (m_subject)
		m_subject->RegisterObserver(this);
}
