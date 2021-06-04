#pragma once

#include "../Core/Includes.h"
#include "../Graphics/Image.h"
#include "../Plane/SimpleRect.h"

namespace MachGL {

	class Splash {

		private:
			WindowDimension m_windowDimension;
			Graphics::MACH_IMAGE m_image;
			Plane::MACH_SIMPLE_RECT m_splash;
			
		public:
			Splash() = default;
			~Splash() = default;
			Splash(const WindowDimension& windowDimension, const Graphics::MACH_IMAGE& image);
			void render();

			inline void setAlpha(const float& alpha) { m_splash->setAlpha(alpha); }
	};

	using MACH_SPLASH = sPoint<Splash>;
}
