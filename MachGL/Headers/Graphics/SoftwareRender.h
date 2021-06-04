/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Plane/SimpleRect.h"
#include "Image.h"

namespace MachGL {
	namespace Graphics {

		class SoftwareRender {
			
			private: 
				float2					  m_position;
				uint32_t                  m_width, m_height;
				WindowDimension           m_windowDimension;
				GLuint					  m_TID;
				Plane::MACH_SIMPLE_RECT   m_rect;
				Graphics::MACH_IMAGE      m_image;

			public:
				uint32_t*                 pixels;

			public:
				SoftwareRender() = default;
				SoftwareRender(const float2& position, const uint32_t& width, const uint32_t& height, const WindowDimension& windowDimension);
				~SoftwareRender();
				void render();
				void clear(const uint32_t& color);
				
			private:
				void init();
				void flush();
		};
	}
}
