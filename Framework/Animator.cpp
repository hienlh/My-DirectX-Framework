#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "ResourceManager.h"

using namespace Framework;

bool CAnimator::Init()
{
	return true;
}

void CAnimator::Release()
{
}


/**
 * \brief The first time you add animation into animator, 
 * it'll set that animation into the root animation of the animator
 */
CAnimator* CAnimator::AddAnimation(CWString animationName)
{
	CAnimation* anim = CResourceManager::GetInstance()->GetAnimation(animationName);

	if (anim) {
		if (m_Animations.size() <= 0) m_pCurrentAnimation = anim;
		m_Animations[animationName] = anim;
	}

	if (!m_pRootAnimation) m_pRootAnimation = anim;
	return this;
}


/**
 * \brief Add transition into Animator
 * \param srcAnimationName Name of source animation 
 * \param dstAnimationName Name of destination animation
 * \param hasExitTime change animation immediately, not wait for source animation finishing
 * \param conditionName A condition is to allow to change animation
 * \param value Value of the condition
 * \param relatedTo To the destination animation change in correctly index of source animation
 */
CAnimator* CAnimator::AddTransition(CWString srcAnimationName, CWString dstAnimationName, bool hasExitTime,
                                    CWString conditionName, bool value, bool relatedTo)
{
	CAnimation *srcAnimation = m_Animations[srcAnimationName];
	CAnimation *dstAnimation = m_Animations[dstAnimationName];

	if (srcAnimation && dstAnimation && srcAnimation != dstAnimation)
	{
		CTransition* transition = nullptr;
		SAFE_ALLOC1(transition, CTransition, dstAnimationName);
		if (conditionName != L"")
			transition->SetCondition(conditionName, value)->SetHasExitTime(hasExitTime)->SetRelatedTo(relatedTo);

		m_transitions[srcAnimationName].push_back(transition);
		return this;
	}
	else
		return nullptr;
}


/**
 * \brief Set the root animation, 
 * if this animation is not in the animator, 
 * it'll be added into
 * \param animationName 
 * \return nullptr if animation is not in Resource Manager
 */
CAnimator* CAnimator::SetRootAnimation(CWString animationName)
{
	bool result = true;
	do
	{
		if (m_Animations.count(animationName))
		{
			m_pRootAnimation = m_Animations[animationName];
		}
		else
		{
			CAnimation* anim = CResourceManager::GetInstance()->GetAnimation(animationName);
			if(anim)
			{
				AddAnimation(animationName);
				m_pRootAnimation = anim;
			}
			else
			{
				result = false;
			}
		}

	} while (false);

	return result ? this : nullptr;
}

CAnimation* CAnimator::GetCurrentAnimation() const
{
	return m_pCurrentAnimation;
}

CSprite* CAnimator::GetCurrentSprite() const
{
	return m_pCurrentAnimation->GetSprite();
}

CTransition* CAnimator::GetTransition(CWString srcAnimationName, CWString dstAnimationName)
{
	if (!m_transitions.count(srcAnimationName)) return nullptr;

	std::list<CTransition*> transitions = m_transitions[srcAnimationName];

	for (CTransition* transition : transitions)
	{
		if (transition->GetDestinationAnimationName() == dstAnimationName) return transition;
	}

	CDebug::Log("Warning GetTransition: Transition '%s' to '%s' is not in animator", srcAnimationName, dstAnimationName);
	return nullptr;
}

CAnimator* CAnimator::AddBool(CWString name, bool value)
{
	bool result;
	do { 
		result = !m_boolConditions.count(name);
		if (result)
		{
			m_boolConditions[name] = value;
		}
	} while (false);

	if (!result) CDebug::Log("Error AddBool: Bool '%s' has been added before", name);
	return result ? this : nullptr;
}

CAnimator* CAnimator::SetBool(CWString name, bool value)
{
	bool result;
	do {
		result = m_boolConditions.count(name);
		if (result)
		{
			m_boolConditions[name] = value;
		}
	} while (false);

	return result ? this : nullptr;
}

bool CAnimator::GetBool(CWString name)
{
	if (m_boolConditions.count(name))
	{
		return m_boolConditions[name];
	}

	CDebug::Log("Error GetBool: Bool '%s' is not in Animator", name);
	return false;
}

void CAnimator::Update(DWORD dt)
{
	std::list<CTransition*> &transitionList = m_transitions[m_pCurrentAnimation->GetName()];

	bool found = true;
	for (CTransition* transition : transitionList)
	{
		std::map<CWString, bool> conditions = transition->GetConditions();
		for (const std::pair<CWString, bool> condition : conditions)
		{
			if (m_boolConditions.count(condition.first))
			{
				if (m_boolConditions[condition.first] != condition.second)
				{
					found = false;
					break;
				}
			} 
			else
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			if (transition->GetHasExitTime() || m_pCurrentAnimation->IsLastFrame()) {

				CAnimation* desAnimation = m_Animations[transition->GetDestinationAnimationName()];
				if (!transition->GetRelatedTo()) {
					desAnimation->Refresh();
				}
				else
				{
					desAnimation->SetIndexCurrentFrame(m_pCurrentAnimation->GetIndexCurrentFrame() + 1);
				}
				m_pCurrentAnimation = desAnimation;
			}
			break;
		}
		found = true;
	}

	m_pCurrentAnimation->Update(dt);
}

void CAnimator::Render()
{
	//if (!m_pCurrentAnimation) return;
	//CSprite* sprite = m_pCurrentAnimation->GetSprite();
	//CTransform* pTransform = m_pGameObject->GetComponent<CTransform>();
	//Vector3 position3D = Vector3(pTransform->Get_Position());
	//position3D.z = 0;

	//CGraphic::GetInstance()->Draw(sprite, &position3D);
}

CAnimator* CAnimator::Instantiate()
{
	CAnimator* instance = nullptr;
	SAFE_ALLOC(instance, CAnimator);

	if (!instance->Init())
	{
		instance->Release();
		SAFE_DELETE(instance);
	}

	return instance;
}

void CAnimator::Destroy(CAnimator*& instance)
{
	if (instance)
	{
		instance->Release();
		SAFE_DELETE(instance);
	}
}
