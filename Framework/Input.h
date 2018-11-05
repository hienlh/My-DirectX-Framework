#pragma once

namespace Framework
{
	class CInput final
	{
		// Used for singleton pattern
	private:
		static CInput* __instance;
<<<<<<< HEAD
		
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
=======

		// Cons / Des
	private:
>>>>>>> origin/dev
		CInput() = default;
		~CInput() = default;
		
		// Properties
	private:
		BYTE m_prevKeys[256] = { 0 };
		BYTE m_keys[256] = { 0 };
		
		MouseState m_mouseState = { 0 };

		Input* m_pInput = nullptr;
		InputDevice* m_pMouseDevice = nullptr;
		InputDevice* m_pKeyboardDevice = nullptr;

		// Internal methods
	private:
		bool Init();
		void Release();

		bool CreateInput();
		bool CreateKeyBoardDevice();
		bool CreateMouseDevice();

		// Public methods
	public:
		bool GetKeyDown(BYTE key);
		bool GetKeyUp(BYTE key);
		bool GetButtonDown(BYTE button);
		
		void Update();

		// Static methods
	public:
		static void Instantiate();
		static void Destroy();
<<<<<<< HEAD

		void PollKeyboard();
		int KeyDown(int key);
		int KeyUp(int key);
		void KillKeyboard();
		void PollMouse();
		int ButtonDown(int button);
		int ButtonUp(int button);
		int Mouse_X();
		int Mouse_Y();
		void KillMouse();
=======
		static CInput* GetInstance();
>>>>>>> origin/dev
	};
}