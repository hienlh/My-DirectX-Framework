#pragma once
#include "stdafx.h"
#include "Object.h"

namespace Framework {
	class CAnimation : public CObject
	{

	public:
		struct SFrame
		{
			CSprite *m_sprite;
			DWORD m_delay = 0;
		};

	private:
		std::vector<SFrame> m_frames = {};

		DWORD m_frameIndex = 0;
		DWORD m_timeElapse = 0;
		DWORD m_defaultTime = 0;

	private:
		CAnimation() = default;
	public:
		CAnimation(CWString name, DWORD defaultTime = 100);
		~CAnimation() = default;

	private:
		bool Init(LPCWSTR textureName, DWORD defaultTime);
		void Render() override;
	public:
		void Update(DWORD dt) override;

	public:
		CSprite* GetSprite() const { return m_frames[m_frameIndex].m_sprite; }

		//Method
	public:
		void Add(SFrame frame);
		void Add(CSprite* sprite, DWORD time = 0);
		bool Add(CWString spriteName, DWORD time = 0);
	};
}
