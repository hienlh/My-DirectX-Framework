#pragma once
#include "Header.h"
#include "Component.h"

namespace Framework
{
	class CRenderer final : public CComponent
	{
		// Properties
	private:
		Texture m_texture = nullptr;
		float _width = -1, _height = -1;

		//Getter / Setter
	public:
		Texture GetTexture() const { return m_texture; }
		float GetWidth() const { return _width; }
		float GetHeight() const { return _height; }
		Vector2 GetSize() const { return Vector2(_width, _height); }

		void SetTexture(LPTSTR texture_path);
		//void SetTexture(Texture texture) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		void SetWidth(float width) { _width = width; }
		void SetHeight(float height) { _height = height; }

		// Cons / Des
	public:
		CRenderer() = default;
		CRenderer(CGameObject* game_object) : CComponent(game_object) {}
		//CRenderer(Object::CGameObject* game_object, Texture texture) : CComponent(game_object) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		CRenderer(CGameObject* game_object, LPCSTR texture_path) : CComponent(game_object) { this->Init(texture_path); }
		virtual ~CRenderer() = default;

		// Internal methods
	private:
		bool Init(LPCSTR texturePath);
		void Release() const;

		// Static methods
	public:
		static CRenderer* Instantiate();
		static CRenderer* Instantiate(UObjectData data);
		static void Destroy(CRenderer* &instance);

		//Override method
	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}
