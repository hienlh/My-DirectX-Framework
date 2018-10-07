#include "Input.h"
#include "Direct3DCore.h"
using namespace Framework::Base;

CInput::CInput()
{
}


CInput::~CInput()
{
}

bool CInput::Init()
{
	m_dinput = IDirect3DCore::GetInstance()->CreateDirect();
	m_dikeyboard = IDirect3DCore::GetInstance()->CreateKeyboard(m_dinput);
	m_dimouse = IDirect3DCore::GetInstance()->CreateKeyboard(m_dinput);
	return m_dikeyboard && m_dinput && m_dimouse;
}

void CInput::PollKeyboard()
{
	m_dikeyboard->GetDeviceState(sizeof(m_keys), reinterpret_cast<LPVOID>(m_keys));
}

int CInput::KeyDown(int key)
{
	return KEY_DOWN(key);
}

void CInput::KillKeyboard()
{
	if (m_dikeyboard != nullptr)
	{
		m_dikeyboard->Unacquire;
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