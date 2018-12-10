#pragma once
#include "stdafx.h"

namespace Framework
{
	// Object class
	class CObject {
		// Properties
	protected:
		CWString m_Name = L"";

		//Getter / Setter
	public:
		CWString GetName() const { return m_Name; }

		void SetName(CWString name) { m_Name = name; }

		// Cons / Des
	public:
		CObject() = default;
		virtual ~CObject() = default;

		// Abstract Classes
	public:
		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;
	};
}