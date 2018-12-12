#include "stdafx.h"
#include "Sprite.h"
#include "ResourceManager.h"

using namespace Framework;

CSprite::CSprite(Texture *texture, Rect sourceRect, Vector2 anchor)
{
	m_pTexture = texture;
	m_sourceRect = sourceRect != Rect(0,0,0,0) ? sourceRect : Rect(0, 0, m_pTexture->height, m_pTexture->width);
	m_anchor = anchor;
}

CSprite::~CSprite()
{
	delete m_pTexture;
}

//bool CSprite::SetTexture(std::string textureName)
//{
//	if (m_pTexture = CResourceManager::GetInstance()->GetTexture(textureName)) 
//		return true;
//	return false;
//}
