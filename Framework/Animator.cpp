#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "ResourceManager.h"

using namespace Framework;

CAnimator::CAnimator(const CAnimator& animator) : CComponent(animator)
{
	m_Name = animator.m_Name;
	m_boolConditions = animator.m_boolConditions;
	for (const std::pair<const std::basic_string<char>, CAnimation*> animation : animator.m_Animations)
	{
		const auto clone = animation.second->Clone();
		AddAnimation(clone);

		if (animator.m_pRootAnimation == animation.second)
			m_pRootAnimation = clone;
	}

	m_transitions = animator.m_transitions;
	for (std::pair<const std::basic_string<char>, std::list<CTransition*>> listTransition : animator.m_transitions)
	{
		std::list<CTransition*> cloneList = {};
		for (CTransition* transition : listTransition.second)
		{
			cloneList.push_back(transition->Clone());
		}
		m_transitions[listTransition.first] = cloneList;
	}

	m_pCurrentAnimation = m_pRootAnimation;
}

bool CAnimator::Init()
{
	return true;
}

void CAnimator::Release()
{
}


/**
 * \brief Deep copy. The first time you add animation into animator, 
 * it'll set that animation into the root animation of the animator
 */
CAnimator* CAnimator::AddAnimation(std::string animationName)
{
	CAnimation* anim = CResourceManager::GetInstance()->GetAnimation(animationName);

	if (anim) {
		if (m_Animations.size() <= 0) m_pCurrentAnimation = anim;
		m_Animations[animationName] = anim->Clone();
	}

	if (!m_pRootAnimation) m_pRootAnimation = m_Animations[animationName];
	return this;
}


/**
 * \brief Note: shallow copy
 * \param animation 
 * \return Return nullptr neu trung ten
 */
CAnimator* CAnimator::AddAnimation(CAnimation* animation)
{
	m_Animations[animation->GetName()] = animation;
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
CAnimator* CAnimator::AddTransition(std::string srcAnimationName, std::string dstAnimationName, bool hasExitTime,
	std::string conditionName, bool value, bool relatedTo)
{
	CAnimation *srcAnimation = m_Animations[srcAnimationName];
	CAnimation *dstAnimation = m_Animations[dstAnimationName];

	if (srcAnimation && dstAnimation && srcAnimation != dstAnimation)
	{
		CTransition* transition = nullptr;
		SAFE_ALLOC1(transition, CTransition, dstAnimationName);
		if (conditionName != "")
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
CAnimator* CAnimator::SetRootAnimation(std::string animationName)
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

CAnimation* CAnimator::GetCurrentAnimation()
{
	if (!m_pCurrentAnimation) m_pCurrentAnimation = m_pRootAnimation;
	return m_pCurrentAnimation;
}

CSprite* CAnimator::GetCurrentSprite()
{
	return GetCurrentAnimation()->GetSprite();
}

CTransition* CAnimator::GetTransition(std::string srcAnimationName, std::string dstAnimationName)
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

CAnimator* CAnimator::AddBool(std::string name, bool value)
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

CAnimator* CAnimator::SetBool(std::string name, bool value)
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

bool CAnimator::GetBool(std::string name)
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
		std::map<std::string, bool> conditions = transition->GetConditions();
		for (const std::pair<std::string, bool> condition : conditions)
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
					desAnimation->SetIndexCurrentFrame(m_pCurrentAnimation->GetIndexCurrentFrame());
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

CAnimator* CAnimator::Clone() const
{
	return new CAnimator(*this);
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
