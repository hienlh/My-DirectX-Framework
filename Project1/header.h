#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include <Windows.h>

//d3d9.lib; d3dx9.lib; dinput8.lib; XInput.lib; dxguid.lib;

// Window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef LPDIRECT3DTEXTURE9 Texture;

