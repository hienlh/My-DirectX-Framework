#include "stdafx.h"
#include "ResourceManager.h"
#include "Graphic.h"

using namespace Framework;

CResourceManager *CResourceManager::__instance = nullptr;

CResourceManager* CResourceManager::GetInstance()
{
	if (!__instance)
		SAFE_ALLOC(__instance, CResourceManager);
	return __instance;
}

Texture* CResourceManager::GetTexture(CWString name) const
{
	const auto it = m_pTextures.find(name);

	if (it != m_pTextures.end())
	{
		return it->second;
	}

	return nullptr;
}

CSprite* CResourceManager::GetSprite(CWString name) const
{
	const auto it = m_pSprites.find(name);

	if (it != m_pSprites.end())
	{
		return it->second;
	}

	return nullptr;
}

CAnimation* CResourceManager::GetAnimation(CWString name) const
{
	const auto it = m_pAnimations.find(name);

	if (it != m_pAnimations.end())
	{
		return it->second;
	}

	return nullptr;
}

bool CResourceManager::AddTexture(CWString name, CWString path, Color transparentColor)
{
	if(m_pTextures.count(name))
	{
		CDebug::Log(L"Texture \"%s\" added! If you want to edit, let use EditTexture function!\n", name);
		return false;
	}

	if (auto tmp = CGraphic::GetInstance()->CreateTexture(path, transparentColor)) {
		m_pTextures[name] = tmp;
		return true;
	}

	CDebug::Log(L"Fail to create texture \"%s\" and add to ResourceManager");
	return false;
}

bool CResourceManager::EditTexture(CWString name, CWString path, Color transparentColor)
{
	if (auto tmp = CGraphic::GetInstance()->CreateTexture(path, transparentColor)) {
		m_pTextures[name] = tmp;
		return true;
	}
	
	CDebug::Log(L"Fail to create texture \"%s\" and add to ResourceManager");
	return false;
}

bool CResourceManager::AddAnimation(CWString name, CAnimation* animation)
{
	if (m_pAnimations.count(name))
	{
		CDebug::Log(L"Animation \"%s\" added! If you want to edit, let use EditAnimation function!\n", name);
		return false;
	}

	m_pAnimations.insert({ name, animation });
	return true;
}

bool CResourceManager::AddSprite(CWString name, CSprite *sprite)
{
	if (m_pSprites.count(name))
	{
		CDebug::Log(L"Sprite \"%s\" added!\n", name);
		return false;
	}

	m_pSprites[name] = sprite;
	return true;
}
