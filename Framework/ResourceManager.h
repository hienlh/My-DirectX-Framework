#pragma once
#include "Animation.h"

namespace Framework 
{
	class CResourceManager
	{
	private:
		static CResourceManager* __instance;

		std::map<LPCWSTR, Texture*> m_pTextures = {};
		std::map<LPCWSTR, CAnimation*> m_pAnimations = {};

	public:
		CResourceManager() = default;

		//Getter / Setter
	public:
		static CResourceManager* GetInstance();
		Texture* GetTexture(LPCWSTR name) const;
		CAnimation* GetAnimation(LPCWSTR name) const;

		//Method
	public:
		void AddTexture(LPCWSTR name, LPCWSTR path);
		void AddAnimation(LPCWSTR name, CAnimation* animation);
	};
}
