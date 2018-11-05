#pragma once
#include "Component.h"

namespace Framework
{
	class CTransform final : public CComponent
	{
	public:
		Vector2 m_position = VECTOR2_ZERO;
		Vector2 m_localPosition = VECTOR2_ZERO;
		Vector2 m_rotation = VECTOR2_ZERO;
		Vector2 m_localRotation = VECTOR2_ZERO;
		Vector2 m_scale = VECTOR2_ONE;
		Vector2 m_localScale = VECTOR2_ONE;

		// Cons / Des
	public:
		CTransform() = default;
		virtual ~CTransform() = default;

		// Getters / Setters
	public:
		Vector2 Get_Position() { return m_position; }
		Vector2 Get_Rotation() { return m_rotation; }
		Vector2 Get_Scale() { return m_scale; }

		void Set_Position(Vector2 position) { m_position = position; }
		void Set_Rotation(Vector2 rotation) { m_rotation = rotation; }
		void Set_Scale(Vector2 scale) { m_scale = scale; }

	public:
		//void Update(Vector3 position = VECTOR3_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector3 scale = VECTOR3_ONE);
		void Update(DWORD dt) override {};
		void Render() override {};

<<<<<<< HEAD
		/// <summary>Like Position += Distance</summary> 
		void PlusPosition(Vector2 distance) { m_position += distance; }

=======
		// Internal methods
>>>>>>> origin/dev
	private:
		bool Init(Vector2 position = VECTOR2_ZERO, Vector2 rotation = VECTOR2_ZERO, Vector2 local_scale = VECTOR2_ONE);
		void Release();

		// Static methods
	public:
		static CTransform* Instantiate(Vector2 position);
		static CTransform* Instantiate(UObjectData data = { {} });
		static void Destroy(CTransform *instance);

		// Override methods
	public:


	};
}
