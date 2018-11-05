#pragma once

#define APP_TITLE L"My DirectX App"


<<<<<<< HEAD
#define KEY_DOWN(key) (key & 0x80 ? 1 : 0)
//#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BUTTON_DOWN(obj, button)((obj.rgbButtons[button] & 0x80)? 1: 0)
=======
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BUTTON_DOWN(obj, button) ((obj.rgbButtons[button] &0x80)? 1: 0)
>>>>>>> origin/dev

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TANK_PATH L"..\\Resources\\tank.png"
#define MARIO_PATH L"..\\Resources\\mario.png"
#define FULL_SCREEN false

#define FRAME_RATE 60

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_ALLOC(p, object_type) if (!p) { p = new object_type(); }

#define VECTOR3_ZERO { 0, 0, 0 } 
#define VECTOR3_ZERO { 0, 0, 0 }
#define VECTOR3_ONE { 1, 1, 1 }

#define VECTOR2_ZERO { 0, 0 } 
#define VECTOR2_ZERO { 0, 0 }
#define VECTOR2_ONE { 1, 1 }

#define COLOR_BLACK D3DCOLOR_XRGB(0, 0, 0)
#define COLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

// Flag
#define OVER_X 13
#define OVER_Y 45