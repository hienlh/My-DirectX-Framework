#include "stdafx.h"
#include "GameSubject.h"
#include "GameObserver.h"
#include "Component.h"
#include "GameObject.h"
#include "GameManager.h"

void Framework::CGameSubject::NotifyWakeUp()
{
	/*for (CObserver* const observer : m_observers)
	{
		if(dynamic_cast<CGameObserver*>(observer))
		{
			dynamic_cast<CGameObserver*>(observer)->WakeUp();
		}
	}*/
}

void Framework::CGameSubject::NotifyStart()
{
	for (int i = 0; i < m_observers.size(); ++i)
	{
		if (const auto component = dynamic_cast<CComponent*>(m_observers[i])) {
			if (component->GetGameObject()->IsInCurrentScene() && dynamic_cast<CGameObserver*>(m_observers[i]))
			{
				dynamic_cast<CGameObserver*>(m_observers[i])->Start();
			}
		}
	}
}

void Framework::CGameSubject::NotifyOnDestroy()
{
	/*for (CObserver* const observer : m_observers)
	{
		if (dynamic_cast<CGameObserver*>(observer))
		{
			dynamic_cast<CGameObserver*>(observer)->OnDestroy();
		}
	}*/
}
