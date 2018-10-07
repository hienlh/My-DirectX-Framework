#pragma once
#include "Header.h"

namespace Framework
{
	namespace Base
	{
		class CInput
		{
		private:
			char m_keys[256];
			LPDIRECTINPUT8 m_dinput;
			LPDIRECTINPUTDEVICE8 m_dimouse;
			LPDIRECTINPUTDEVICE8 m_dikeyboard;
			DIMOUSESTATE m_mouseState;
		public:
			CInput() = default;
			~CInput() = default;
			bool Init();
			void PollKeyboard();
			int KeyDown(int key);
			void KillKeyboard();
			void PollMouse();
			int MouseButton(int button);
			int Mouse_X();
			int Mouse_Y();
			void KillMouse();
		};
	}
}
