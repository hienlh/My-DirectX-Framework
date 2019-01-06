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
									Vector2(child->IntAttribute("w") != 0 ? child->IntAttribute("w") : child->IntAttribute("width"),
										child->IntAttribute("h")!= 0 ? child->IntAttribute("h") : child->IntAttribute("height")
									) };
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

Texture* CResourceManager::GetTexture(std::string name) const
{
	const auto it = m_pTextures.find(name);

	if (it != m_pTextures.end())
	{
		return it->second;
	}

	CDebug::Log("GetTexture: No texture name '%s'\n", name.c_str());
	return nullptr;
}

CAnimation* CResourceManager::GetAnimation(std::string name) const
{
	const auto it = m_pAnimations.find(name);

	if (it != m_pAnimations.end())
	{
		return it->second;
	}

	CDebug::Log("GetAnimation: No animation name '%s'\n", name.c_str());
	return nullptr;
}

CSprite* CResourceManager::GetSprite(std::string textureName, DWORD index) const
{
	return GetSprite(GetTexture(textureName), index);
}

CSprite* CResourceManager::GetSprite(Texture* texture, DWORD index)
{
	if (index == -1)
	{
		return new CSprite(texture);
	}
	return texture->m_sprites[index];
}

CGameObject* CResourceManager::GetPrefab(std::string name)
{
	if (!m_pPrefabs.count(name))
	{
		CDebug::Log("GetPrefab: No prefab name '%s'\n", name.c_str());
		return nullptr;
	}

	return m_pPrefabs[name];
}

bool CResourceManager::AddTexture(const std::string &name, const std::string &path, const Color &transparentColor, const char* xmlPath, const Vector2 &defaultAnchor)
{
	if(m_pTextures.count(name))
	{
		CDebug::Log(L"Texture \"%s\" added! If you want to edit, let use EditTexture function!\n", name);
		return false;
	}

	if (auto tmp = CGraphic::GetInstance()->CreateTexture(path, transparentColor)) {
		if(xmlPath)
		{
			std::vector<Rect> rects = ParseXML(xmlPath, 1);
			const DWORD size = rects.size();
			for (int i = 0; i < size; i++)
			{
				tmp->m_sprites.push_back(new CSprite(tmp, rects[i], defaultAnchor));
			}
		}
		else tmp->m_sprites.push_back(new CSprite(tmp)); //Add a only one sprite with size equal texture

		m_pTextures[name] = tmp;
		return true;
	}

	CDebug::Log(L"AddTexture: Fail to create texture \"%s\" and add to ResourceManager", name.c_str());
	return false;
}

bool CResourceManager::AddAnimation(std::string name, CAnimation* animation)
{
	if (m_pAnimations.count(name))
	{
		CDebug::Log(L"AddAnimation: Animation \"%s\" added! If you want to edit, let use EditAnimation function!\n", name.c_str());
		return false;
	}

	m_pAnimations.insert({ name, animation });
	return true;
}

/**
 * \brief Add Prefab from an existed GameObject or create new gameObject
 */
CGameObject* CResourceManager::AddPrefab(std::string name, CGameObject* gameObject)
{
	if (m_pPrefabs.count(name))
	{
		CDebug::Log("AddPrefab: Prefab '%s' has been added", name.c_str());
		return nullptr;
	}

	CGameObject* result = nullptr;

	if(gameObject) result = new CGameObject(*gameObject);
	else result = new CGameObject(name, VECTOR2_ZERO, false);

	m_pPrefabs[name] = result;
	return result;
}
