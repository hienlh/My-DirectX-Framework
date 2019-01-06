#pragma once
#include "stdafx.h"
#include "GameManager.h"
#include "dsutil.h"
//#include "dxutil.h"

namespace Framework
{
	class CAudio final
	{
	private:
		static CAudio* __instance;

		// Primary DirectSound object 
		CSoundManager *m_soundManager = nullptr;
		
	public:
		CSound* Load(CString fileName);
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

		void Update();
	};
}