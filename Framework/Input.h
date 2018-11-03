#pragma once

namespace Framework
{
	class CInput final
	{
		// Used for singleton pattern
	private:
		static CInput* __instance;

		// Cons / Des
	private:
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
		static CInput* GetInstance();
	};
}