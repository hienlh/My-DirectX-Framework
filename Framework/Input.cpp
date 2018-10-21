#include "Input.h"
#include "Graphic.h"
using namespace Framework;

CInput* CInput::__instance = nullptr;

bool CInput::Init()
{
	m_dinput = CGraphic::GetInstance()->CreateDirect();
	m_dikeyboard = CGraphic::GetInstance()->CreateKeyboard(m_dinput);
	m_dimouse = CGraphic::GetInstance()->CreateMouse(m_dinput);
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

void CInput::PollKeyboard()
{
	m_dikeyboard->GetDeviceState(sizeof(m_keys), reinterpret_cast<LPVOID>(m_keys));
}

int CInput::KeyDown(int key)
{
	return KEY_DOWN(key);
}

int CInput::KeyUp(int key)
{
	return KEY_UP(key);
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
	m_dimouse->GetDeviceState(sizeof(m_mouseState), reinterpret_cast<LPVOID>(m_keys));
}

bool CInput::GetKeyDown(BYTE key)
{
	return BUTTON_DOWN(m_mouseState, Button);
}

bool CInput::GetKeyUp(BYTE key)
{
	return m_mouseState.lX;
}

bool CInput::GetButtonDown(BYTE button)
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
	if(!__instance)
		Instantiate();

	return __instance;
}