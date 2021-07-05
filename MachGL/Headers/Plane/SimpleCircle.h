/*

Mach::GL (Alpha) 


*/

#pragma once

#include "SimpleRect.h"

namespace MachGL {
	namespace Plane {

		class SimpleCircle {
			
			MACH_SIMPLE_RECT m_rect;

			public:
				SimpleCircle(const float2& position, const float2& size, const Graphics::MACH_IMAGE& image, const WindowDimension& windowDimension) {

                    RectProperties properties;
                    properties.position = position;
                    properties.size = size;
                    properties.image = image;
					m_rect = make_sPoint<SimpleRect>(properties, windowDimension);
					m_rect->setRadius(size.x / 2);
                    m_rect->create();
				}

				SimpleCircle(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension) {

                    RectProperties properties;
                    properties.position = position;
                    properties.size = size;
                    properties.color = color;
					m_rect = make_sPoint<SimpleRect>(properties, windowDimension);
					m_rect->setRadius(size.x / 2);
                    m_rect->create();
				}

				~SimpleCircle() {  }
				void render() { m_rect->render(); }
		};

		using MACH_SIMPLE_CIRCLE = sPoint<SimpleCircle>;
	}
}
