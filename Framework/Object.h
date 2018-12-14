#pragma once
#include "stdafx.h"

namespace Framework
{
	// Object class
	class CObject {
		// Properties
	protected:
		std::string m_Name = "";

		//Getter / Setter
	public:
		std::string GetName() const { return m_Name; }

		void SetName(std::string name) { m_Name = name; }

		// Cons / Des
	public:
		CObject(const CObject& object);
		CObject() = default;
		virtual ~CObject() = default;

		// Abstract Classes
	public:
		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;

		virtual CObject* Clone() const = 0;
	};
}