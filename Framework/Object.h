#pragma once
#include "stdafx.h"

namespace Framework
{
	// Object class
	class CObject {
		// Properties
	protected:

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