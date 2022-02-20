/*

Mach::GL (Alpha)

*/

#include "../../../Headers/API/OpenGL/OpenGLEnvironmentMap.h"

namespace MachGL {
	namespace Graphics {

		OpenGLEnvironmentMap::OpenGLEnvironmentMap(const float& size, const WindowDimension& windowDimension) : EnvironmentMap::EnvironmentMap(size, windowDimension) { 
		
			init();
		}

		void OpenGLEnvironmentMap::init() {

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
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				MACH_ERROR_MSG("Framebuffer is not complete");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void OpenGLEnvironmentMap::renderFace(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const uint32_t& face) {

			Object::Camera tempCamera = camera;

			m_shader->enable();
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, m_textureColorBuffer, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_shader->setUniformMatrix4fv("_vw_matrix", tempCamera.getViewMatrix(face));

			for (uint32_t i = 0; i < objects.size(); i++) {

				m_renderer->submit(objects[i]);
			}

			m_shader->disable();
		}

		void OpenGLEnvironmentMap::capture() {

			glViewport(0, 0, (GLsizei)m_size, (GLsizei)m_size);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
		}

		void OpenGLEnvironmentMap::stop() {

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, m_windowDimension.width, m_windowDimension.height);
		}
	}
}
