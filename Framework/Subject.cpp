#include "stdafx.h"
#include "Subject.h"

using namespace Framework;

CSubject::CSubject(const CSubject& subject)
{
	m_observers = subject.m_observers;
}

void CSubject::RegisterObserver(CObserver* observer)
{
	const auto it = std::find(m_observers.begin(), m_observers.end(), observer);
	if (it == m_observers.end()) //Not found
		m_observers.push_back(observer);
}

void CSubject::RemoveObserver(CObserver* observer)
{
	const auto it = std::find(m_observers.begin(), m_observers.end(), observer);
	if (it != m_observers.end()) // Found
		m_observers.erase(it);
}
