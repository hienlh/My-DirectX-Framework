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

Texture* CResourceManager::GetTexture(LPCWSTR name) const
{
	const auto it = m_pTextures.find(name);

	if (it != m_pTextures.end())
	{
		return it->second;
	}

	return nullptr;
}

CAnimation* CResourceManager::GetAnimation(LPCWSTR name) const
{
	const auto it = m_pAnimations.find(name);

	if (it != m_pAnimations.end())
	{
		return it->second;
	}

	return nullptr;
}

void CResourceManager::AddTexture(LPCWSTR name, LPCWSTR path)
{
	m_pTextures.insert({ name, CGraphic::GetInstance()->CreateTexture(path) });
}

void CResourceManager::AddAnimation(LPCWSTR name, CAnimation* animation)
{
	m_pAnimations.insert({ name, animation });
}
