#pragma once
#include "Component.h"

namespace Framework
{
	class CTransform final : public CComponent
	{
	private:
		CTransform* m_pParent = nullptr;
		std::set<CTransform*> m_pChildren = {};
		Vector2 m_position = VECTOR2_ZERO;
		Vector3 m_rotation = VECTOR3_ZERO;
		Vector2 m_scale = VECTOR2_ONE;

		// Cons / Des
	public:
		CTransform() = default;
		CTransform(const CTransform &transform);
		explicit CTransform(CGameObject* game_object, Vector2 position = VECTOR2_ZERO, Vector3 rotation = VECTOR3_ZERO, Vector2 scale = VECTOR2_ONE);
		virtual ~CTransform() = default;

		CTransform& operator=(const CComponent& component) override;

		// Getters / Setters
	public:
		Vector2 Get_Position() const;
		Vector3 Get_Rotation() const;
		Vector2 Get_Scale() const;
		Vector2 GetLocalPosition() const { return m_position; }
		Vector3 GetLocalRotation() const { return m_rotation; }
		Vector2 GetLocalScale() const { return m_scale; }
		CTransform* GetParent() const { return m_pParent; }

		CTransform* Set_Position(const Vector2 &position, const bool &inWorldSpace = true);
		CTransform* Set_Rotation(const Vector3 &rotation);
		CTransform* Set_Scale(const Vector2 &scale);
		CTransform* SetParent(CTransform *parent);
		CTransform* SetParent(CGameObject *parentGameObject);

		/**
		 * \brief Like Position += Distance
		 * \param distance 
		 */
		CTransform* PlusPosition(Vector2 distance) { m_position += distance;  return this; }

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
		void Update(const DWORD &dt) override {}
		void Render() override {}
		CTransform* Clone() override { return new CTransform(*this); }

		//Methods
	public:
		CTransform* Translate(const Vector2 &translate) { m_position += translate;  return this; }
	};
}
