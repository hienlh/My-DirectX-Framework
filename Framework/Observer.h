#pragma once
#include "Subject.h"

/*
 * Created by hienlh1298 on Dec 24th 2018
 */

namespace Framework
{
	class CObserver
	{
	private:
		CSubject* m_subject = nullptr;

	public:
		CObserver() = default;
		CObserver(CSubject* subject) { m_subject = subject; AddToSubject(); }
		CObserver(const CObserver& observer) { m_subject = observer.m_subject; AddToSubject(); }
		virtual ~CObserver();

	public:
		void AddToSubject();
	};
}
