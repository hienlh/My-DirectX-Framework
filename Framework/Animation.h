#pragma once
#include "stdafx.h"
#include "Object.h"

namespace Framework {
	class CAnimation : public CObject
	{

	public:
		struct SFrame
		{
			Rect m_rect;
			DWORD m_delay = 0;
		};

	private:
		Texture* m_pTexture = nullptr;
		std::vector<SFrame> m_frames = {};

		DWORD m_frameIndex = 0;
		DWORD m_timeElapse = 0;
		DWORD m_defaultTime = 0;

	private:
		CAnimation() = default;
		~CAnimation() = default;

	private:
		void Init(LPCWSTR textureName, DWORD defaultTime);
		void Render() override;
	public:
		void Update(DWORD dt) override;

	public:
		Texture* GetTexture() const { return m_pTexture; }
		Rect GetRect() { return m_frames[m_frameIndex].m_rect; }

		//Method
	public:
		void Add(SFrame frame);
		void Add(Rect rect, DWORD time = 0);

	public:
		static CAnimation* Instantiate(LPCWSTR name, LPCWSTR textureName, DWORD defaultTime);
	};
}
