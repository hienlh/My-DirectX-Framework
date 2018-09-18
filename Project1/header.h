#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <time.h>
#include <Windows.h>

#define APP_TITLE "My DirectX App"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) &0x8000)? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) &0x8000)? 1 : 0)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FILE_NAME "..\Resources\tank.png"
#define FULL_SCREEN FALSE

#define FRAME_RATE 30

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_ALLOC(p, object_type) if (!p) { p = new object_type(); }

// Window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);