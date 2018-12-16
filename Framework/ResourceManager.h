#pragma once
#include "Animation.h"
#include "GameObject.h"

namespace Framework 
{
	class CResourceManager
	{
	private:
		static CResourceManager* __instance;

		std::map<std::string, Texture*> m_pTextures = {};
		std::map<std::string, CAnimation*> m_pAnimations = {};
		std::map<std::string, CGameObject*> m_pPrefabs = {};

	public:
		CResourceManager() = default;

		//Getter / Setter
	public:
		static CResourceManager* GetInstance();
		Texture* GetTexture(std::string name) const;
		CAnimation* GetAnimation(std::string name) const;
		CSprite* GetSprite(std::string textureName, DWORD index = -1) const;
		static CSprite* GetSprite(Texture* texture, DWORD index = -1);
		CGameObject* GetPrefab(std::string name);

		//Method
	public:
		bool AddTexture(std::string name, std::string path, Color transparentColor = COLOR_BLACK, const char* xmlPath = nullptr);
		//static bool EditTexture(std::string name, std::string path, Color transparentColor = COLOR_BLACK, const char* xmlPath = nullptr);
		
		CGameObject* AddPrefab(std::string name, CGameObject *gameObject = nullptr);

	private:
		bool AddAnimation(std::string name, CAnimation* animation);

	private:
		friend class CAnimation;
		friend class CSprite;
	};
}
