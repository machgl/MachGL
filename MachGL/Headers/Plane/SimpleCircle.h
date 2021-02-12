/*

Mach::GL (Alpha) 


*/

#pragma once

#include "SimpleRect.h"

namespace MachGL {
	namespace Plane {

		class SimpleCircle {
			
			SimpleRect* m_rect;

			public:
				SimpleCircle(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const float& windowWidth, const float& windowHeight) {

					m_rect = new SimpleRect(position, size, image, windowWidth, windowHeight);
					m_rect->setRadius(size.x / 2);
				}

				SimpleCircle(const float2& position, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight) {

					m_rect = new SimpleRect(position, size, color, windowWidth, windowHeight);
					m_rect->setRadius(size.x / 2);
				}

				~SimpleCircle() {  }
				void render() { m_rect->render(); }
		};
	}
}
