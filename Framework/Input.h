#pragma once
#include "stdafx.h"

namespace Framework
{
	class CInput final
	{
	private:
		static CInput* __instance;

		char m_prevKeys[256] = { 0 };
		char m_keys[256] = { 0 };

		DIMOUSESTATE m_mouseState = { 0 };
		DIMOUSESTATE m_prevMouseState = { 0 };

		LPDIRECTINPUT8 m_dinput = nullptr;
		LPDIRECTINPUTDEVICE8 m_dimouse = nullptr;
		LPDIRECTINPUTDEVICE8 m_dikeyboard = nullptr;


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

		Input *CreateInput();
		InputDevice *CreateKeyboard(Input *input);
		InputDevice *CreateMouse(Input *dinput);

		void Update();
		void PollKeyboard();
		int KeyDown(int key);
		int KeyUp(int key); 
		int KeyHold(int key);
		void KillKeyboard();
		void PollMouse();
		int ButtonDown(int button);
		int ButtonUp(int button);
		int Mouse_X();
		int Mouse_Y();
		void KillMouse();
	};
}