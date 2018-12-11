#pragma once
#include "Animation.h"

namespace Framework 
{
	class CResourceManager
	{
	private:
		static CResourceManager* __instance;

		std::unordered_map<CWString, Texture*> m_pTextures = {};
		std::unordered_map<CWString, CAnimation*> m_pAnimations = {};

	public:
		CResourceManager() = default;

		//Getter / Setter
	public:
		static CResourceManager* GetInstance();
		Texture* GetTexture(CWString name) const;
		CAnimation* GetAnimation(CWString name) const;
		CSprite* GetSprite(CWString textureName, DWORD index) const;
		static CSprite* GetSprite(Texture* texture, DWORD index);

		//Method
	public:
		bool AddTexture(CWString name, CWString path, Color transparentColor = COLOR_BLACK, const char* xmlPath = nullptr);
		static bool EditTexture(CWString name, CWString path, Color transparentColor = COLOR_BLACK, const char* xmlPath = nullptr);
	private:
		bool AddAnimation(CWString name, CAnimation* animation);

	private:
		friend class CAnimation;
		friend class CSprite;
	};
}
