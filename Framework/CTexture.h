#pragma once
#include "Graphic.h"

class CTexture
{
private:
	IDirect3DTexture9* texture;
	DWORD width;
	DWORD height;

public:
	CTexture() = default;
	~CTexture()
	{
		texture->Release();
	}

	IDirect3DTexture9* GetTexture() const { return texture; }
	DWORD GetWidth() const { return width; }
	DWORD GetHeight() const { return height; }
};
