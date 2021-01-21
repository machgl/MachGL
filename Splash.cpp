#include "Splash.h"

namespace MachGL {

	Splash::Splash(const float& width, const float& height, Graphics::Image* image)
		: m_width(width), m_height(height), m_image(image) {

		m_splash = new Graphics::SimpleRect(float2(0, 0), float2(m_width, m_height), m_image, m_width, m_height);
	}

	void Splash::render() {

		m_splash->render();
	}
}