#pragma once
#include "stdafx.h"
#include "dsutil.h"

namespace Framework
{
	class CAudio final
	{
	private:
		static CAudio* __instance;

		// Primary DirectSound object 
		CSoundManager *m_soundManager = nullptr;

	public:
		CSound* Load(CString fileName) const;
		void Play(CSound* pSound);
		void PlayLoop(CSound* pSound);
		void Stop(CSound* pSound);

	public:
		static CAudio* GetInstance();

	public:
		CAudio() = default;
		~CAudio() = default;

	private:

		bool Init();
		void Release();

	public:
		static void Instantiate();
		static void Destroy();
	};
}