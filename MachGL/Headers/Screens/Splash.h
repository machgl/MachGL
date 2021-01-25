#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Graphics/Image.h"
#include "../../Headers/Graphics/SimpleRect.h"

namespace MachGL {

	class Splash {

		private:
			float m_width, m_height;
			Graphics::Image* m_image;
			Graphics::SimpleRect* m_splash;
			
		public:
			Splash(const float& width, const float& height, Graphics::Image* image);
			void render();

			inline void setAlpha(const float& alpha) { m_splash->setAlpha(alpha); }
	};
}