#pragma once

#include "../Core/Includes.h"
#include "../Graphics/Image.h"
#include "../Plane/SimpleRect.h"

namespace MachGL {

	class Splash {

		private:
			WindowDimension m_windowDimension;
			sPoint<Graphics::Image> m_image;
			Plane::SimpleRect* m_splash;
			
		public:
			Splash(const WindowDimension& windowDimension, const sPoint<Graphics::Image>& image);
			void render();

			inline void setAlpha(const float& alpha) { m_splash->setAlpha(alpha); }
	};
}