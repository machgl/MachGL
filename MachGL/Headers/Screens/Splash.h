#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Graphics/Image.h"
#include "../../Headers/Graphics/SimpleRect.h"

namespace MachGL {

	class Splash {

		private:
			float m_width, m_height;
			std::shared_ptr<Graphics::Image> m_image;
			std::unique_ptr<Graphics::SimpleRect> m_splash;
			
		public:
			Splash(const float& width, const float& height, const std::shared_ptr<Graphics::Image>& image);
			void render();

			inline void setAlpha(const float& alpha) { m_splash->setAlpha(alpha); }
	};
}