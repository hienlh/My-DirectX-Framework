#pragma once
#include "Subject.h"

/*
 * Created by hienlh1298 on Dec 24th 2018
 */

namespace Framework
{
	class CGameSubject : public CSubject
	{
	public:
		CGameSubject() = default;
		CGameSubject(const CSubject& subject)
			: CSubject(subject)
		{
		}

		virtual ~CGameSubject() = default;

		//Method
	public:
		void NotifyWakeUp();
		void NotifyStart();
		void NotifyOnDestroy();
	};
}
