#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "Graphic.h"
#include "ResourceManager.h"

using namespace Framework;

bool CAnimator::Init()
{
	//m_pGameObject->AddComponent<CRenderer>();

	return true;
}

void CAnimator::Release()
{
	for (std::map<LPCWSTR, CState*>::iterator it = m_states.begin(); it != m_states.end(); it++)
		SAFE_FREE(it->second);
}

bool CAnimator::AddState(LPCWSTR stateName)
{
	CAnimation* animation = CResourceManager::GetInstance()->GetAnimation(stateName);

	// Resource found
	if (animation)
	{
		SAFE_ALLOC1(m_states[stateName], CState, animation);

		if (m_states.size() == 1)
			m_currentState = m_states[stateName];

		return true;
	}
	// Resource not found
	else
		return false;
}

bool CAnimator::SetCurrentState(LPCWSTR stateName)
{
	if (m_states[stateName])
	{
		m_currentState = m_states[stateName];
		return true;
	}
	else
		return false;
}

CTransition* Framework::CAnimator::AddTransition(LPCWSTR srcStateName, LPCWSTR dstStateName)
{
	CState *srcState = m_states[srcStateName];
	CState *dstState = m_states[dstStateName];

	if (srcState && dstState && srcState != dstState)
	{
		CTransition* transition = nullptr;
		SAFE_ALLOC1(transition, CTransition, dstStateName);

		m_transitions[srcStateName].push_back(transition);
		return transition;
	}
	else
		return nullptr;
}

bool Framework::CAnimator::AddBool(LPCWSTR name, bool value)
{
	if (m_boolConditions.find(name) == m_boolConditions.end())
	{
		m_boolConditions[name] = value;
		return true;
	}
	else
		return false;
}

bool Framework::CAnimator::SetBool(LPCWSTR name, bool value)
{
	if (m_boolConditions.find(name) != m_boolConditions.end())
	{
		m_boolConditions[name] = value;
	}
	else
		return false;
}

bool Framework::CAnimator::GetBool(LPCWSTR name)
{
	if (m_boolConditions.find(name) != m_boolConditions.end())
	{
		return m_boolConditions[name];
	}
	else
		return false;
}

void CAnimator::Update(DWORD dt)
{
	std::list<CTransition*> &transitionList = m_transitions[m_currentState->GetName()];

	bool found = false;
	for (CTransition* transition : transitionList)
	{
		std::map<CWString, bool> conditions = transition->GetMapCondition();
		for (const std::pair<CWString, bool> &condition : conditions)
		{
			if (m_boolConditions.find(condition.first) != m_boolConditions.end())
			{
				if (m_boolConditions[condition.first] == condition.second)
				{
					m_currentState = m_states[transition->GetDestinationStateName()];
					found = true;
					break;
				}
			}
		}
		if (found)
			break;
	}

	m_currentState->GetAnimation()->Update(dt);
}

void CAnimator::Render()
{
	CAnimation* animation = m_currentState->GetAnimation();
	Texture* pTexture = animation->GetTexture();
	CTransform* pTransform = m_pGameObject->GetComponent<CTransform>();
	Rect rect = animation->GetRect();
	Vector3 pos = Vector3(pTransform->Get_Position());
	pos.z = 0;
	
	CRenderer* renderer = m_pGameObject->GetComponent<CRenderer>();
	renderer->SetTexture(pTexture);
	renderer->SetWidth(rect.Size().x)->SetHeight(rect.Size().y);
	renderer->SetRenderPosX(rect.left)->SetRenderPosY(rect.top);
	renderer->SetZOrder(pTransform->Get_Rotation().z);
	renderer->Render();
	
	//CGraphic::GetInstance()->Draw(pTexture, &pos, &rect, nullptr, pTransform->Get_Rotation().z);
}

CAnimator* CAnimator::Instantiate()
{
	CAnimator* instance = nullptr;
	SAFE_ALLOC(instance, CAnimator);

	if (!instance->Init())
	{
		instance->Release();
		SAFE_FREE(instance);
	}

	return instance;
}

void CAnimator::Destroy(CAnimator*& instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_FREE(instance);
	}
}

Framework::CState::CState(CAnimation * animation)
{
	m_animation = animation;
}
