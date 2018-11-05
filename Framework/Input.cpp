#include "stdafx.h"

#include "Input.h"
#include "Macros.h"
#include "Graphic.h"
#include "Window.h"

using namespace Framework;

CInput* CInput::__instance = nullptr;

bool CInput::Init()
{
<<<<<<< HEAD
	m_dinput = CGraphic::GetInstance()->CreateDirect();
	m_dikeyboard = CGraphic::GetInstance()->CreateKeyboard(m_dinput);
	m_dimouse = CGraphic::GetInstance()->CreateMouse(m_dinput);
	
	return m_dikeyboard && m_dinput && m_dimouse;
=======
	bool result = false;
	do
	{
		if (!CreateInput())
			break;

		if (!CreateKeyBoardDevice())
			break;

		if (!CreateMouseDevice())
			break;

		result = true;
	} while (false);

	return result;
>>>>>>> origin/dev
}

void CInput::Release()
{
	if (m_pKeyboardDevice)
	{
		m_pKeyboardDevice->Unacquire();
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = nullptr;
	}

	if (m_pMouseDevice)
	{
		m_pMouseDevice->Unacquire();
		m_pMouseDevice->Release();
		m_pMouseDevice = nullptr;
	}

	if (m_pInput)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

bool CInput::CreateInput()
{
<<<<<<< HEAD
	std::copy(m_keys, m_keys + 256, m_prevKeys);
	m_dikeyboard->GetDeviceState(sizeof(m_keys), reinterpret_cast<LPVOID>(m_keys));
=======
	return (DirectInput8Create(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W, reinterpret_cast<LPVOID*>(&m_pInput), nullptr) == DI_OK);	
>>>>>>> origin/dev
}

bool CInput::CreateKeyBoardDevice()
{
<<<<<<< HEAD
	return KEY_DOWN(m_keys[key]) && !KEY_DOWN(m_prevKeys[key]);
=======
	bool result = false;
	do
	{
		if (m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, nullptr) != DI_OK)
			break;

		if (m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
			break;

		if (m_pKeyboardDevice->SetCooperativeLevel(CWindow::GetInstance()->Get_WindowHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
			break;

		if (m_pKeyboardDevice->Acquire() != DI_OK)
			break;

		result = true;
	} while (false);

	return result;
>>>>>>> origin/dev
}

bool CInput::CreateMouseDevice()
{
<<<<<<< HEAD
	return !KEY_DOWN(m_keys[key]) && KEY_DOWN(m_prevKeys[key]);
=======
	bool result = false;
	do
	{
		if (m_pInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, nullptr) != DI_OK)
			break;

		if (m_pMouseDevice->SetDataFormat(&c_dfDIMouse) != DI_OK)
			break;

		if (m_pMouseDevice->SetCooperativeLevel(CWindow::GetInstance()->Get_WindowHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
			break;

		result = m_pMouseDevice->Acquire();
		if (result != DI_OK)
			break;

		result = true;
	} while (false);

	return result;
>>>>>>> origin/dev
}

void Framework::CInput::Instantiate()
{
	if (!__instance)
	{
		SAFE_ALLOC(__instance, CInput);

		if (!__instance->Init())
		{
			__instance->Release();
			SAFE_DELETE(__instance);
		}
	}
}

void CInput::Destroy()
{
<<<<<<< HEAD
	memcpy_s(&m_prevMouseState, sizeof(m_prevMouseState), &m_mouseState, sizeof(m_mouseState));
	m_dimouse->GetDeviceState(sizeof(m_mouseState), reinterpret_cast<LPVOID>(&m_mouseState));
}

int CInput::ButtonDown(int button)
{
	return BUTTON_DOWN(m_mouseState, button) && !BUTTON_DOWN(m_prevMouseState, button);
}

int CInput::ButtonUp(int button)
{
	return !BUTTON_DOWN(m_mouseState, button) && BUTTON_DOWN(m_prevMouseState, button);
=======
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

bool CInput::GetKeyDown(BYTE key)
{
	return KEY_DOWN(key);
>>>>>>> origin/dev
}

bool CInput::GetKeyUp(BYTE key)
{
	return KEY_UP(key);
}

bool CInput::GetButtonDown(BYTE button)
{
	return BUTTON_DOWN(m_mouseState, button);
}

void CInput::Update()
{
	m_pKeyboardDevice->GetDeviceState(sizeof(m_keys), reinterpret_cast<LPVOID>(m_keys));
	m_pMouseDevice->GetDeviceState(sizeof(m_mouseState), reinterpret_cast<LPVOID>(&m_mouseState));
}

CInput* CInput::GetInstance()
{
	return __instance;
}