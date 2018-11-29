#pragma once
#include "Component.h"

namespace Framework
{
	class CTransform final : public CComponent
	{
	public:
		Vector2 m_position = VECTOR2_ZERO;
		Vector2 m_localPosition = VECTOR2_ZERO;
		Vector3 m_rotation = VECTOR3_ZERO;
		Vector3 m_localRotation = VECTOR3_ZERO;
		Vector2 m_scale = VECTOR2_ONE;
		Vector2 m_localScale = VECTOR2_ONE;

		// Cons / Des
	public:
		CTransform() = default;
		CTransform(CGameObject* game_object, Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector2 local_scale = VECTOR2_ONE);
		virtual ~CTransform() = default;

		// Getters / Setters
	public:
		Vector2 Get_Position() const { return m_position; }
		Vector3 Get_Rotation() const { return m_rotation; }
		Vector2 Get_Scale() const { return m_scale; }

		CTransform* Set_Position(Vector2 position) { m_position = position; return this; }
		CTransform* Set_Rotation(Vector3 rotation) { m_rotation = rotation; return this; }
		CTransform* Set_Scale(Vector2 scale) { m_scale = scale; return this; }

		/// <summary>Like Position += Distance</summary> 
		void PlusPosition(Vector2 distance) { m_position += distance; }

		// Internal methods
	private:
		bool Init(Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector2 local_scale = VECTOR2_ONE);
		void Release();

		// Static methods
	public:
		static CTransform* Instantiate(Vector2 position);
		static void Destroy(CTransform *instance);

		// Override methods
	public:
		void Update(DWORD dt) override;
		void Render() override;

	};
}
