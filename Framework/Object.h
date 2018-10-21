#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macros.h"
#include "Header.h"

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
