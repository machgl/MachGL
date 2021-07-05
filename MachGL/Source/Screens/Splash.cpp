#include "../../Headers/Screens/Splash.h"

namespace MachGL {

	Splash::Splash(const WindowDimension& windowDimension, const Graphics::MACH_IMAGE& image)
		: m_windowDimension(windowDimension), m_image(image) {

            Plane::RectProperties properties;
            properties.size = float2(m_windowDimension.width, m_windowDimension.height);
            properties.image = m_image;
            m_splash = make_sPoint<Plane::SimpleRect>(properties, m_windowDimension);
            m_splash->create();
	}

	void Splash::render() {

		m_splash->render();
	}
}
