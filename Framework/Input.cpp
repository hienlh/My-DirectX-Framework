#include "stdafx.h"
#include "Input.h"
#include "GameManager.h"
using namespace Framework;

CInput* CInput::__instance = nullptr;

bool CInput::Init()
{
	m_dinput = CreateInput();
	m_dikeyboard = CreateKeyboard(m_dinput);
	m_dimouse = CreateMouse(m_dinput);

	return m_dikeyboard && m_dinput && m_dimouse;
}

void CInput::Release()
{
	if (m_dinput)
		m_dinput->Release();
	if (m_dikeyboard)
		m_dikeyboard->Release();
	if (m_dimouse)
		m_dimouse->Release();
}

void CInput::Instantiate()
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
	__instance->Release();
	SAFE_DELETE(__instance);
}

Input *Framework::CInput::CreateInput()
{
	Input *dinput = nullptr;
	HRESULT result = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<LPVOID*>(&dinput), nullptr);

	if (result != DI_OK)
		dinput = nullptr;

	return dinput;
}

InputDevice * Framework::CInput::CreateKeyboard(Input *dinput)
{
	HWND hwnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	LPDIRECTINPUTDEVICE8 dikeyboard = nullptr;

	do
	{
		HRESULT result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
		if (result != DI_OK)
			break;

		result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (result != DI_OK)
			break;

		result = dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (result != DI_OK)
			break;

		result = dikeyboard->Acquire();
		if (result != DI_OK)
			break;

	} while (false);

	return dikeyboard;
}

InputDevice * Framework::CInput::CreateMouse(Input *dinput)
{
	HWND hwnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	LPDIRECTINPUTDEVICE8 dimouse = nullptr;
	do
	{
		HRESULT result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
		if (result != DI_OK)
			break;

		result = dimouse->SetDataFormat(&c_dfDIMouse);
		if (result != DI_OK)
			break;

		result = dimouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (result != DI_OK)
			break;

		result = dimouse->Acquire();
		if (result != DI_OK)
			break;

	} while (false);

	return dimouse;
}

void CInput::Update()
{
	// Fixed can not interact game input after switch window
	HWND hwnd = CGameManager::GetInstance()->GetWindow()->Get_WindowHandle();
	m_dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_dikeyboard->Acquire();
	m_dimouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_dimouse->Acquire();

	// Update keyboard and mouse
	PollKeyboard();
	PollMouse();
}

void CInput::PollKeyboard()
{
	std::copy(m_keys, m_keys + sizeof(m_keys), m_prevKeys);
	m_dikeyboard->GetDeviceState(sizeof(m_keys), reinterpret_cast<LPVOID>(m_keys));
}

int CInput::KeyDown(const int &key)
{
	return m_keys[key] && !m_prevKeys[key];
}

int CInput::KeyUp(const int &key)
{
	return !m_keys[key] && m_prevKeys[key];
}

int CInput::KeyHold(const int &key)
{
	return m_keys[key] && m_prevKeys[key];
}

void CInput::KillKeyboard()
{
	if (m_dikeyboard != nullptr)
	{
		m_dikeyboard->Unacquire();
		m_dikeyboard->Release();
		m_dikeyboard = nullptr;
	}
}

void CInput::PollMouse()
{
	memcpy_s(&m_prevMouseState, sizeof(m_prevMouseState), &m_mouseState, sizeof(m_mouseState));
	m_dimouse->GetDeviceState(sizeof(m_mouseState), reinterpret_cast<LPVOID>(&m_mouseState));
}

int CInput::ButtonDown(const int &button)
{
	return m_mouseState.rgbButtons[button] && !m_prevMouseState.rgbButtons[button];
	//return BUTTON_DOWN(m_mouseState, button) && !BUTTON_DOWN(m_prevMouseState, button);
}

int CInput::ButtonUp(const int &button)
{
	return !m_mouseState.rgbButtons[button] && m_prevMouseState.rgbButtons[button];
	//return !BUTTON_DOWN(m_mouseState, button) && BUTTON_DOWN(m_prevMouseState, button);
}

int CInput::Mouse_X()
{
	return m_mouseState.lX;
}

int CInput::Mouse_Y()
{
	return m_mouseState.lY;
}

void CInput::KillMouse()
{
	if (m_dimouse != nullptr)
	{
		m_dimouse->Unacquire();
		m_dimouse->Release();
		m_dimouse = nullptr;
	}
}

CInput* CInput::GetInstance()
{
	if (!__instance)
		Instantiate();

	return __instance;
}