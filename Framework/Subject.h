#pragma once

/*
 * Created by hienlh1298 on Dec 24th 2018
 */

namespace Framework
{
	class CObserver;

	class CSubject
	{
		//Cons / Des
	public:
		CSubject() = default;
		CSubject(const CSubject& subject);
		virtual ~CSubject() = default;

		//Properties
	protected:
		std::vector<CObserver*> m_observers = {};

		//Method
	public:
		void RegisterObserver(CObserver* observer);
		void RemoveObserver(CObserver *observer);
	};
}
