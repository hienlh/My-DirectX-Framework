#pragma once

#define APP_TITLE L"My DirectX App"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BUTTON_DOWN(obj, button) ((obj.rgbButtons[button] &0x80)? 1: 0)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
#define COLOR_GREEN D3DCOLOR_XRGB(0, 255, 0)
#define COLOR_RED D3DCOLOR_XRGB(255, 0, 0)
#define COLOR_BLUE D3DCOLOR_XRGB(0, 0, 255)

// Flag
#define OVER_X 13
#define OVER_Y 38