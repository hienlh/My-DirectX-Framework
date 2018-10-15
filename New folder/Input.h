#pragma once
#include "Header.h"

namespace Framework
{
	namespace Base
	{
		class CInput
		{
		private:
			static CInput* __instance;

			char m_keys[256] = { 0 };

			LPDIRECTINPUT8 m_dinput = nullptr;
			LPDIRECTINPUTDEVICE8 m_dimouse = nullptr;
			LPDIRECTINPUTDEVICE8 m_dikeyboard = nullptr;

			DIMOUSESTATE m_mouseState = { 0 };

		public:
			static CInput* GetInstance(); 

		public:
			CInput() = default;
			~CInput() = default;

		private:
			bool Init();
			void Release();

		public:
			static void Instantiate();
			static void Destroy();

			void PollKeyboard();
			int KeyDown(int key);
			int KeyUp(int key);
			void KillKeyboard();
			void PollMouse();
			int MouseButton(int button);
			int Mouse_X();
			int Mouse_Y();
			void KillMouse();
		};
	}
}
