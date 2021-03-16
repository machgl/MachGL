/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/EnvironmentMap.h"

namespace MachGL {
	namespace Graphics {

		EnvironmentMap::EnvironmentMap(const float& size, const WindowDimension& windowDimension) 
			: m_size(size), m_windowDimension(windowDimension) { 
			
			init();
		}

		void EnvironmentMap::init() {

			glGenFramebuffers(1, &m_fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

			glGenTextures(1, &m_textureColorBuffer);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureColorBuffer);

			for (int i = 0; i < 6; i++)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, (GLsizei)m_size, (GLsizei)m_size, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			glGenRenderbuffers(1, &m_rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, (GLsizei)m_size, (GLsizei)m_size);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				MACH_ERROR_MSG("Framebuffer is not complete");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void EnvironmentMap::reflectedObjects(const std::vector<Object::Object>& objects) {

			glViewport(0, 0, m_size, m_size);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (int i = 0; i < 6; i++) {

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_textureColorBuffer, 0);
				m_renderer.submit(objects);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, m_windowDimension.width, m_windowDimension.height);
		}
	}
}
