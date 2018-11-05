#include "stdafx.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameManager.h"
#include "Renderer.h"
#include "Animator.h"

using namespace Framework;

<<<<<<< HEAD
bool CGameObject::Init()
=======
//Temp for deadline
bool CGameObject::leftBlockMoveDown = true;
bool CGameObject::rightBlockMoveDown = true;

bool CGameObject::AddComponent(SBuilder builder)
>>>>>>> origin/dev
{
	bool result = false;
	if (builder.type == EObjectType::RENDERER && !m_rendererComponent)
	{
		m_rendererComponent = reinterpret_cast<CRenderer*>(CComponent::Instantiate(builder));
		if(m_rendererComponent)
			m_rendererComponent->SetParentObject(this);
		result = true;
	}
	else if (builder.type == EObjectType::TRANSFORM && !m_transformComponent)
	{
		m_transformComponent = reinterpret_cast<CTransform*>(CComponent::Instantiate(builder));
		if (m_transformComponent)
			m_transformComponent->SetParentObject(this);
		result = true;
	}
	else if (builder.type == EObjectType::ANIMATOR && !m_animatorComponent)
	{
		m_animatorComponent = reinterpret_cast<CAnimator*>(CComponent::Instantiate(builder));
		if (m_animatorComponent)
			m_animatorComponent->SetParentObject(this);
		result = true;
	}

	return result;
}
/*
bool CGameObject::RemoveComponent(EObjectType type)
{
	bool result = false;

	if (type == EObjectType::RENDERER && m_rendererComponent)
	{
		CComponent::Destroy(reinterpret_cast<CComponent*&>(m_rendererComponent));
		result = true;
	}
	if (type == EObjectType::TRANSFORM && m_transformComponent)
	{
		CComponent::Destroy(reinterpret_cast<CComponent*&>(m_transformComponent));
		result = true;
	}

	return result;
}*/

bool CGameObject::Init()
{
	m_rendererComponent = nullptr;
	m_transformComponent = nullptr;
	m_rigidBodyComponent = nullptr;

	return true;
}

void CGameObject::Release()
{
	for (CComponent* pComponent : m_components)
		CComponent::Destroy(pComponent);

	/*if (m_rendererComponent)
		CRenderer::Destroy(m_rendererComponent);

	if (m_transformComponent)
		CTransform::Destroy(m_transformComponent);*/
}

CGameObject* CGameObject::Instantiate(String name, Vector2 position)
{
	CGameObject* instance = nullptr;
	bool result = false;
	do
	{
		SAFE_ALLOC(instance, CGameObject);

		if (!instance->Init())
			break;

		Framework::UObjectData data = { {} };
		data.transformData = { position, VECTOR2_ZERO, VECTOR2_ONE };
		instance->AddComponent({ EObjectType::TRANSFORM, data });
		if (!instance->GetTransform())
			break;
		
		CScene* pScene = CGameManager::GetInstance()->GetCurrentScene();
		if (!pScene)
			break;
		
		pScene->AddGameObject(instance);

		result = true;
	} while (false);

	if (!result)
	{
		if (instance)
			instance->Release();
		SAFE_DELETE(instance);
<<<<<<< HEAD

	instance->m_Name = name;
	instance->AddComponent<CTransform>()->Set_Position(position);

=======
	}
>>>>>>> origin/dev
	return instance;
}

void CGameObject::Destroy(CGameObject*& instance)
{
	instance->Release();
	SAFE_DELETE(instance);
}
void CGameObject::Update(DWORD dt)
{
<<<<<<< HEAD
	for (auto component : m_pComponents)
	{
		component->Update(dt);
	}
=======
	/*for (CComponent* pComponent : m_components)
		pComponent->Update(dt);*/

	if (m_rendererComponent)
		m_rendererComponent->Update(dt);
	
	if (m_transformComponent)
		m_transformComponent->Update(dt);
	
	if (m_rigidBodyComponent)
		m_rigidBodyComponent->Update(dt);
	
	if (m_animatorComponent)
		m_animatorComponent->Update(dt);
>>>>>>> origin/dev
}

void CGameObject::Render()
{
	/*for (CComponent* pComponent : m_components)
		pComponent->Render();*/

	if (m_rendererComponent)
		m_rendererComponent->Render();

	if (m_animatorComponent)
		m_animatorComponent->Render();
}