#include "stdafx.h"
#include "Macros.h"
#include "Animator.h"
#include "ResourceManager.h"

using namespace Framework;

CTransition::CTransition(const CTransition& transition)
	: CObject(transition)
{
	m_hasExitTime = transition.m_hasExitTime;
	m_isRelatedTo = transition.m_isRelatedTo;
	m_dstAnimationName = transition.m_dstAnimationName;
	m_conditions = transition.m_conditions;
}

CAnimator::CAnimator(const CAnimator& animator) : CComponent(animator)
{
	m_Name = animator.m_Name;
	m_boolConditions = animator.m_boolConditions;
	for (const std::pair<const std::basic_string<char>, CAnimation*> animation : animator.m_Animations)
	{
		const auto clone = new CAnimation(*animation.second);
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
			cloneList.push_back(new CTransition(*transition));
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
CAnimator* CAnimator::AddAnimation(const std::string& animationName)
{
	CAnimation* anim = CResourceManager::GetInstance()->GetAnimation(animationName);

	if (anim) m_Animations[animationName] = new CAnimation(*anim);

	if (!m_pRootAnimation)
	{
		m_pRootAnimation = m_Animations[animationName];
		m_pCurrentAnimation = m_pRootAnimation;
	}
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
CAnimator* CAnimator::AddTransition(const std::string& srcAnimationName, const std::string& dstAnimationName,
	const bool& hasExitTime, const std::string& conditionName, const bool& value, const bool& relatedTo)
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
CAnimator* CAnimator::SetRootAnimation(const std::string &animationName)
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

CTransition* CAnimator::GetTransition(const std::string& srcAnimationName, const std::string& dstAnimationName)
{
	if (!m_transitions.count(srcAnimationName)) return nullptr;

	std::list<CTransition*> transitions = m_transitions[srcAnimationName];

	for (CTransition* transition : transitions)
	{
		if (transition->GetDestinationAnimationName() == dstAnimationName) return transition;
	}

	CDebug::Log("Warning GetTransition: Transition '%s' to '%s' is not in animator", srcAnimationName.c_str(), dstAnimationName.c_str());
	return nullptr;
}

CAnimator* CAnimator::AddBool(const std::string& name, const bool& value)
{
	bool result;
	do { 
		result = !m_boolConditions.count(name);
		if (result)
		{
			m_boolConditions[name] = value;
		}
	} while (false);

	if (!result) CDebug::Log("Error AddBool: Bool '%s' has been added before", name.c_str());
	return result ? this : nullptr;
}

CAnimator* CAnimator::SetBool(const std::string& name, const bool& value)
{
	bool result;
	do {
		result = m_boolConditions.count(name);
		if (result)
		{
			m_boolConditions[name] = value;
		}
	} while (false);

	if (!result) CDebug::Log("SetBool '%s' in '%s' fail!", name.c_str(), m_pGameObject->GetName().c_str());
	return result ? this : nullptr;
}

bool CAnimator::GetBool(std::string name, bool defaultValue)
{
	if (m_boolConditions.count(name))
	{
		return m_boolConditions[name];
	}

	CDebug::Log("Error GetBool: Bool '%s' is not in '%s'", name.c_str(), m_pGameObject->GetName().c_str());
	return defaultValue;
}

void CAnimator::Update(const DWORD &dt)
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

CAnimator& CAnimator::operator=(const CComponent& component)
{
	(*this).CComponent::operator=(component);

	if(const auto pAnim = dynamic_cast<const CAnimator*>(&component))
	{
		for (auto condition : pAnim->m_boolConditions)
		{
			if (m_boolConditions.count(condition.first))
			{
				m_boolConditions[condition.first] = condition.second;
			}
		}

		for (auto animation : pAnim->m_Animations)
		{
			if(m_Animations.count(animation.first))
			{
				*m_Animations[animation.first] = *animation.second;
			}

			if (animation.second == pAnim->m_pCurrentAnimation)
			{
				if (m_Animations.count(animation.first))
				{
					m_pCurrentAnimation = m_Animations[animation.first];
				}
			}

			if (animation.second == pAnim->m_pRootAnimation)
			{
				if (m_Animations.count(animation.first))
				{
					m_pRootAnimation = m_Animations[animation.first];
				}
			}
		}
	}

	return *this;
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
