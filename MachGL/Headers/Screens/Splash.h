#pragma once

#include "../Core/Includes.h"
#include "../Graphics/Image.h"
#include "../Plane/SimpleRect.h"

namespace MachGL {

	class Splash {

		private:
			float m_width, m_height;
			sPoint<Graphics::Image> m_image;
			Plane::SimpleRect* m_splash;
			
		public:
			Splash(const float& width, const float& height, const sPoint<Graphics::Image>& image);
			void render();

			inline void setAlpha(const float& alpha) { m_splash->setAlpha(alpha); }
	};
}