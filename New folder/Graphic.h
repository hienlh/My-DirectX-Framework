#pragma once
#include "Header.h"
#include "GameObject.h"

namespace Framework
{
	namespace Base
	{
		// Direct3D Core Interface
		class IGraphic
		{
			// Cons / Des
		public:
			IGraphic() = default;
			virtual ~IGraphic() = default;
			
			// Getter / Setters
		public:
			virtual Direct3D* Get_Direct3D() = 0;
			virtual Device* Get_Device() = 0;
			virtual Surface* Get_BackBuffer() = 0;
			virtual Sprite* Get_SpriteHandler() = 0;

			// Abstract methods
		public:
			virtual bool Render(std::vector<Framework::Object::CGameObject*> list_game_objects) = 0;
			virtual void Draw(Vector3 position, Texture* texture) = 0;
			virtual Texture* CreateTexture(CString texturePath) = 0;

			// Static methods
		public:
			static void Instantiate(HWND hWnd, bool fullscreen);
			static void Destroy();

			static IGraphic* GetInstance();
		};
	}
}
