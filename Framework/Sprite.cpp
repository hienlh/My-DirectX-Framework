#include "stdafx.h"
#include "Sprite.h"
#include "ResourceManager.h"

using namespace Framework;

CSprite::CSprite(CWString name, CWString textureName, Rect *sourceRect, Vector2 anchor)
{
	CResourceManager *manager = CResourceManager::GetInstance();
	m_pTexture = manager->GetTexture(textureName);
	m_sourceRect = sourceRect ? *sourceRect : Rect(0,0,m_pTexture->height, m_pTexture->width);
	m_anchor = anchor;

	if (!manager->AddSprite(name, this))
		delete this;
}

CSprite::~CSprite()
{
	delete m_pTexture;
}

bool CSprite::SetTexture(CWString textureName)
{
	if (m_pTexture = CResourceManager::GetInstance()->GetTexture(textureName)) 
		return true;
	return false;
}
