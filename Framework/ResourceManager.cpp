#include "stdafx.h"
#include "ResourceManager.h"
#include "Graphic.h"

using namespace Framework;

std::vector<Rect> ParseXML(const char* fileName, size_t depth)
{
	std::vector<Rect> result = {};
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName);

	tinyxml2::XMLElement* parent = doc.FirstChildElement();
	for (size_t iDepth = 0; iDepth < depth - 1; iDepth++)
		parent = parent->FirstChildElement();

	// Count sprites stored in xml for resize
	size_t spriteCount = 0;
	for (tinyxml2::XMLNode* node = parent->FirstChild(); node; node = node->NextSibling())
		spriteCount++;

	result.resize(spriteCount);

	// Load attributes
	tinyxml2::XMLElement* child = parent->FirstChildElement();
	for (size_t iSprite = 0; iSprite < result.size(); iSprite++)
	{
		result[iSprite] = { Vector2(child->IntAttribute("x"), child->IntAttribute("y")),
									Vector2(child->IntAttribute("w"), child->IntAttribute("h")) };
		child = child->NextSiblingElement();
	}

	return result;
}

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

CAnimation* CResourceManager::GetAnimation(CWString name) const
{
	const auto it = m_pAnimations.find(name);

	if (it != m_pAnimations.end())
	{
		return it->second;
	}

	return nullptr;
}

CSprite* CResourceManager::GetSprite(CWString textureName, DWORD index) const
{
	return GetSprite(GetTexture(textureName), index);
}

CSprite* CResourceManager::GetSprite(Texture* texture, DWORD index)
{
	return texture->m_sprites[index];
}

bool CResourceManager::AddTexture(CWString name, CWString path, Color transparentColor, const char* xmlPath)
{
	if(m_pTextures.count(name))
	{
		CDebug::Log(L"Texture \"%s\" added! If you want to edit, let use EditTexture function!\n", name);
		return false;
	}

	if (auto tmp = CGraphic::GetInstance()->CreateTexture(path, transparentColor)) {
		if(xmlPath)
		{
			std::vector<Rect> rects = ParseXML(xmlPath, 2);
			const DWORD size = rects.size();
			for (int i = 0; i < size; i++)
			{
				tmp->m_sprites.push_back(new CSprite(tmp, rects[i]));
			}
		}
		else tmp->m_sprites.push_back(new CSprite(tmp)); //Add a only one sprite with size equal texture

		m_pTextures[name] = tmp;
		return true;
	}

	CDebug::Log(L"Fail to create texture \"%s\" and add to ResourceManager");
	return false;
}

bool CResourceManager::EditTexture(CWString name, CWString path, Color transparentColor, const char* xmlPath)
{
	//TODO Edit texture in ResourceManager
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
