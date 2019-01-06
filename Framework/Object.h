#pragma once
#include "stdafx.h"

namespace Framework
{
	// Object class
	class CObject {
		// Properties
	protected:
		std::string m_Name = "";
		bool m_isActive = true;

		//Getter / Setter
	public:
		std::string GetName() const { return m_Name; }
		bool GetIsActive() const { return m_isActive; }

		void SetName(std::string name) { m_Name = name; }
		void SetIsActive(bool isActive) { m_isActive = isActive; }

		// Cons / Des
	public:
		CObject(const CObject& object);
		CObject() = default;
		virtual ~CObject() = default;

		// Abstract Classes
	public:
		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;
	};
}