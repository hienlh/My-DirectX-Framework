#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

using namespace Framework;

Framework::CGameObject* _gameObject = nullptr;

CWString CComponent::GetName() const
{
	return m_pGameObject->GetName();
}
