#pragma once
#include "Header.h"
#include "Component.h"

namespace Framework
{
	class CRenderer final : public CComponent
	{
		// Properties
	private:
		Texture* m_pTexture = nullptr;
		DWORD m_textureWidth = 0, m_textureHeight = 0;
		
		// Cons / Des
	private:
		CRenderer() = default;
		CRenderer(CGameObject* game_object) : CComponent(game_object) {}
		//CRenderer(Object::CGameObject* game_object, Texture texture) : CComponent(game_object) { m_texture = texture; } //Remove because only if u set texture by path, you can get size of image
		CRenderer(CGameObject* game_object, LPCSTR texture_path) : CComponent(game_object) { this->Init(texture_path); }
		virtual ~CRenderer() = default;

		// Internal methods
	private:
		bool Init(LPCWSTR texturePath);
		void Release();

		// Static methods
	public:
		static CRenderer* Instantiate();
		static void Destroy(CRenderer* &instance);

		// Override method
	public:
		void Update(DWORD dt) override;
		void Render() override;
	};
}
