#pragma once

#define APP_TITLE L"My DirectX App"

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BUTTON_DOWN(obj, button) ((obj.rgbButtons[button] &0x80)? 1: 0)

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define FULL_SCREEN false

#define FRAME_RATE 60

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_ALLOC(p, object_type) if (!p) { p = new object_type(); }
#define SAFE_ALLOC1(p, objectType, param) if (!p) { p = new objectType(param); }

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

#define GRAVITY 0.0005

#define MAX_VELOCITY 1e9
#define EPSILON 1e-9

#define MAX_QUAD_TREE_LEVEL 6
#define COLOR_GET_A( c ) ((c)>>24)
#define COLOR_GET_R( c ) (((c)>>16) & 0xFF)
#define COLOR_GET_G( c ) (((c)>>8)  & 0xFF)
#define COLOR_GET_B( c ) ((c) & 0xFF)

#define DIRECTION_LEFT 00
#define DIRECTION_RIGHT 01
#define DIRECTION_TOP 10
#define DIRECTION_BOTTOM 11