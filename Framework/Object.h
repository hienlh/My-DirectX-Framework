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
		const std::string &GetName() const { return m_Name; }
		virtual bool GetIsActive();

		void SetName(const std::string &name) { m_Name = name; }
		void SetIsActive(const bool &isActive) { m_isActive = isActive; }

		// Cons / Des
	public:
		CObject(const CObject& object);
		CObject() = default;
		virtual ~CObject() = default;

		// Abstract Classes
	public:
		virtual void Update(const DWORD &dt) = 0;
		virtual void Render() = 0;
		CObject& operator=(const CObject& object);
		void CopyValue(const CObject* object);
	};
}