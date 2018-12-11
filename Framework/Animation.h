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
		bool m_loop = true;

	private:
		CAnimation() = default;
	public:
		CAnimation(CWString name, CWString textureName, DWORD startSprite, DWORD count, DWORD defaultTime = 100, bool loop = true);
		~CAnimation() = default;

	private:
		bool Init(LPCWSTR textureName, DWORD defaultTime);
		void Render() override;
	public:
		void Update(DWORD dt) override;

		// Getter / Setter
	public:
		CSprite* GetSprite();
		bool IsLastFrame() const;
		bool GetIndexCurrentFrame() const { return m_frameIndex; }

		CAnimation* SetIndexCurrentFrame(int index);

		//Method
	public:
		CAnimation* Add(CWString textureName, DWORD indexSprite, DWORD pos = -1, DWORD time = 0);
		CAnimation* Add(CSprite* sprite, DWORD pos = -1, DWORD time = 0);
		void Refresh() { m_frameIndex = 0; }
	private:
		CAnimation* Add(SFrame frame);
	};
}
