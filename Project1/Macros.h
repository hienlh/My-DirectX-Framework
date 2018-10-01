#pragma once

#define APP_TITLE "My DirectX App"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) &0x8000)? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) &0x8000)? 1 : 0)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TANK_PATH "E:\\workspace\\My-DirectX-Framework\\Resources\\tank.png"
#define FULL_SCREEN false

#define FRAME_RATE 60

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_ALLOC(p, object_type) if (!p) { p = new object_type(); }

#define VECTOR3_ZERO { 0, 0, 0 }