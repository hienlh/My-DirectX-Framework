#pragma once
#include "Observer.h"
#include "GameSubject.h"

/*
 * Created by hienlh1298 on Dec 24th 2018
 */

namespace Framework
{
	class CGameObserver : public CObserver
	{
	private:
		CGameObserver() = default;
	public:
		explicit CGameObserver(CGameSubject* subject) : CObserver(dynamic_cast<CSubject*>(subject)) {}
		CGameObserver(const CGameObserver& go) = default;
		virtual ~CGameObserver() = default;

		//Method
		virtual void WakeUp() {}
		virtual void Start() {}
		virtual void OnDestroy() {}
	};
}
