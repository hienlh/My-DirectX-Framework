#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Macros.h"
#include "Header.h"

namespace Framework
{
	// Enum for builder
	enum EObjectType
	{
		UNKNOWN = 0,
		GAME_OBJECT = 1,
		TRANSFORM = 2,
		RENDERER = 3,
		RIGIDBODY = 4,
		ANIMATOR = 5
	};

	// Initialize parameters for Game Object
	struct SGameObjectBuilder
	{
	};

	// Initialize parameters for Render Component
	struct SRendererBuilder
	{
		LPCWSTR texturePath = nullptr;
	};

	// Initialize parameters for Transform Component
	struct STransformBuilder
	{
		Vector2 position = VECTOR2_ZERO;
		Vector2 rotation = VECTOR2_ZERO;
		Vector2 scale = VECTOR2_ONE;
	};

	struct SAnimatorBuilder
	{
		LPCWSTR texturePath = nullptr;
		DWORD countWidth = 0, countHeight = 0, count = 0;
		DWORD delay = 0;
	};

	// Builder
	union UObjectData
	{
		SGameObjectBuilder gameObjectData;
		SRendererBuilder renderData;
		STransformBuilder transformData;
		SAnimatorBuilder animatorBuilder;
	};

	// Builder Struct
	struct SBuilder
	{
		EObjectType type = EObjectType::UNKNOWN;
		UObjectData data = { {} };
	};

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
