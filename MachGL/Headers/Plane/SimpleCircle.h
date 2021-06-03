/*

Mach::GL (Alpha) 


*/

#pragma once

#include "SimpleRect.h"

namespace MachGL {
	namespace Plane {

		class SimpleCircle {
			
			sPoint<SimpleRect> m_rect;

			public:
				SimpleCircle(const float2& position, const float2& size, const Graphics::MACH_IMAGE& image, const WindowDimension& windowDimension) {

					m_rect = make_sPoint<SimpleRect>(position, size, image, windowDimension);
					m_rect->setRadius(size.x / 2);
				}

				SimpleCircle(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension) {

					m_rect = make_sPoint<SimpleRect>(position, size, color, windowDimension);
					m_rect->setRadius(size.x / 2);
				}

				~SimpleCircle() {  }
				void render() { m_rect->render(); }
		};
	}
}
