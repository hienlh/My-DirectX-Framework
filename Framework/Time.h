#pragma once
#include "Header.h"

namespace Framework {
	class CTime
	{
	private:
		static CTime *__instance;

		DWORD m_deltaTime;
		DWORD m_time;

		// Cons / Des
	private:
		CTime();
		void Release();
	public:
		~CTime() = default;

		// Getter / Setter
	public:
		DWORD DeltaTime() const { return m_deltaTime; }
		DWORD Time() const { return m_time; }
	private:
		void SetDeltaTime(DWORD dt) { m_deltaTime = dt; }
		void SetTime(DWORD time) { m_time = time; }

		// Static method
	public:
		static CTime *GetInstance();
		static void Destroy();

		//Friends
	public:
		friend class CGameManager;
	};
}