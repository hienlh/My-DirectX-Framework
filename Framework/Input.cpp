#include "stdafx.h"

#include "Input.h"
#include "Macros.h"
#include "Graphic.h"
#include "Window.h"

using namespace Framework;

CInput* CInput::__instance = nullptr;

bool CInput::Init()
{
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
	return (DirectInput8Create(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W, reinterpret_cast<LPVOID*>(&m_pInput), nullptr) == DI_OK);	
}

bool CInput::CreateKeyBoardDevice()
{
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
}

bool CInput::CreateMouseDevice()
{
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
	if (__instance)
	{
		__instance->Release();
		SAFE_DELETE(__instance);
	}
}

bool CInput::GetKeyDown(BYTE key)
{
	return KEY_DOWN(key);
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