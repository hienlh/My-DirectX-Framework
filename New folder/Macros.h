#pragma once

#define APP_TITLE "My DirectX App"


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BUTTON_DOWN(obj,button)((obj.rgbButtons[button] &0x80)? 1: 0)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TANK_PATH "..\\Resources\\tank.png"
#define MARIO_PATH "..\\Resources\\mario.png"
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


#define OVER_X 13
#define OVER_Y 38