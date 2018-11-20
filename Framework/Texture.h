#pragma once

typedef struct Texture
{
	IDirect3DTexture9 *texture;
	DWORD width, height;

	~Texture()
	{
		texture->Release();
	}
};