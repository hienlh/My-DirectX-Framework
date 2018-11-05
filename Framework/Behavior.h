#pragma once
#include "stdafx.h"
#include "Component.h"

namespace Framework {

	class CBehavior : public CComponent
	{

		//Con / Des
	public:
		CBehavior() = default;
		virtual ~CBehavior() = default;

		//Abstract method
	public:
		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;
	};
}