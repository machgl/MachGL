/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/SoftwareRender.h"

namespace MachGL {
	namespace Graphics {

		SoftwareRender::SoftwareRender(const float2& position, const uint32_t& width, const uint32_t& height, const WindowDimension& windowDimension)
			: m_position(position), m_width(width), m_height(height), m_windowDimension(windowDimension) {

			init();
		}

		void SoftwareRender::init() {

			pixels = new uint32_t[static_cast<uint64_t>(m_width) * static_cast<uint64_t>(m_height)];
	
			glGenTextures(1, &m_TID);
			glBindTexture(GL_TEXTURE_2D, m_TID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
			
			m_image = make_uPoint<Graphics::Image>(m_TID);

			clear(0);

			m_rect = make_uPoint<Plane::SimpleRect>(m_position, float2((float)m_width, (float)m_height), m_image->ref(), m_windowDimension);
		}

		void SoftwareRender::clear(const uint32_t& color) {

			for (uint32_t i = 0; i < m_width * m_height; i++) pixels[i] = color;
		}

		void SoftwareRender::flush() {
			
			m_rect->render();

			glBindTexture(GL_TEXTURE_2D, m_TID);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void SoftwareRender::render() {

			flush();
		}

		SoftwareRender::~SoftwareRender() {

			delete[] pixels;
		}
	}
}
