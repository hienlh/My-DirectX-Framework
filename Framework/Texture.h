#pragma once
#include "Sprite.h"

typedef struct Texture
{
	IDirect3DTexture9 *texture;
	DWORD width, height;
	std::vector<Framework::CSprite*> m_sprites = {};

	~Texture()
	{
		texture->Release();
	}
};
