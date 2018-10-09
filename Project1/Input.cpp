#include "Input.h"
#include "Direct3DCore.h"
using namespace Framework::Base;

bool CInput::Init()
{
	m_dinput = IDirect3DCore::GetInstance()->CreateDirect();
	m_dikeyboard = IDirect3DCore::GetInstance()->CreateKeyboard(m_dinput);
	m_dimouse = IDirect3DCore::GetInstance()->CreateMouse(m_dinput);
	return m_dikeyboard && m_dinput && m_dimouse;
}

void CInput::Release()
{
}

void Framework::Base::CInput::Instantiate()
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

int CInput::MouseButton(int Button)
{
	return BUTTON_DOWN(m_mouseState, Button);
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

CInput* CInput::__instance = nullptr;

CInput* CInput::GetInstance()
{
	return __instance;
}