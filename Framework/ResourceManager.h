#pragma once
#include "Animation.h"

namespace Framework 
{
	class CResourceManager
	{
	private:
		static CResourceManager* __instance;

		std::unordered_map<CWString, Texture*> m_pTextures = {};
		std::unordered_map<CWString, CSprite*> m_pSprites = {};
		std::unordered_map<CWString, CAnimation*> m_pAnimations = {};

	public:
		CResourceManager() = default;

		//Getter / Setter
	public:
		static CResourceManager* GetInstance();
		Texture* GetTexture(CWString name) const;
		CSprite* GetSprite(CWString name) const;
		CAnimation* GetAnimation(CWString name) const;

		//Method
	public:
		bool AddTexture(CWString name, CWString path, Color transparentColor = COLOR_BLACK);
		bool EditTexture(CWString name, CWString path, Color transparentColor = COLOR_BLACK);
	private:
		bool AddAnimation(CWString name, CAnimation* animation);
		bool AddSprite(CWString name, CSprite *sprite);

	private:
		friend class CAnimation;
		friend class CSprite;
	};
}
