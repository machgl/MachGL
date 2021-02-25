#include "../../Headers/Screens/Splash.h"

namespace MachGL {

	Splash::Splash(const WindowDimension& windowDimension, const sPoint<Graphics::Image>& image)
		: m_windowDimension(windowDimension), m_image(image) {

		m_splash = new Plane::SimpleRect(float2(0, 0), float2(windowDimension.width, windowDimension.height), m_image, m_windowDimension);
	}

	void Splash::render() {

		m_splash->render();
	}
}