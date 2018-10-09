#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include <Windows.h>

//d3d9.lib; d3dx9.lib; dinput8.lib; XInput.lib; dxguid.lib;

// Window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef D3DXVECTOR3 Vector3;
typedef IDirect3DTexture9 Texture;
typedef LPCSTR CString;
typedef IDirect3D9 Direct3D;
typedef IDirect3DDevice9 Device;
typedef IDirect3DSurface9 Surface;
typedef ID3DXSprite Sprite;