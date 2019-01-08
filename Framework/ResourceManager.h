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
		Texture* GetTexture(const std::string &name) const;
		CAnimation* GetAnimation(const std::string &name) const;
		CSprite* GetSprite(const std::string &textureName, const DWORD &index = -1) const;
		static CSprite* GetSprite(Texture* texture, const DWORD &index = -1);
		CGameObject* GetPrefab(const std::string &name);

		//Method
	public:
		bool AddTexture(const std::string &name, const std::string &path, const Color &transparentColor = COLOR_BLACK, const char* xmlPath = nullptr, const Vector2 &defaultAnchor = { 0.5,0.5 });
		//static bool EditTexture(std::string name, std::string path, Color transparentColor = COLOR_BLACK, const char* xmlPath = nullptr);
		
		CGameObject* AddPrefab(const std::string& name, CGameObject *gameObject = nullptr);

	private:
		bool AddAnimation(const std::string& name, CAnimation* animation);

	private:
		friend class CAnimation;
		friend class CSprite;
	};
}
