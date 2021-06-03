/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/EnvironmentMap.h"

namespace MachGL {
	namespace Graphics {

		EnvironmentMap::EnvironmentMap(const float& size, const WindowDimension& windowDimension) 
			: m_size(size), m_windowDimension(windowDimension) { 
			
            m_renderer = Graphics::Renderer3D::createRenderer();
			m_projection = Maths::Matrix::simplePerspective(90, WindowDimension{ (uint32_t)128, (uint32_t)128 });
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
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				MACH_ERROR_MSG("Framebuffer is not complete");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void EnvironmentMap::capture() {

			glViewport(0, 0, (GLsizei)m_size, (GLsizei)m_size);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
		}

		void EnvironmentMap::reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, Object::Camera& camera, const MACH_SHADER& shader) {

			for (int i = 0; i < 6; i++) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_textureColorBuffer, 0);

				camera.switchToFace(i);
				shader->setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());
				shader->setUniformMatrix4fv("_pr_matrix", m_projection);

				for (uint32_t i = 0; i < objects.size(); i++) {

					shader->setUniform1i("_texture", objects[i]->getTID());
					m_renderer->submit(objects[i]);
				}
			}
		}

		void EnvironmentMap::reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, Object::Camera& camera, const MACH_SHADER& shader, const sPoint<Object::Skybox>& skybox) {

			for (int i = 0; i < 6; i++) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_textureColorBuffer, 0);
				
				camera.switchToFace(i);
				shader->enable();
				shader->setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());
				shader->setUniformMatrix4fv("_pr_matrix", m_projection);
                
				for (uint32_t i = 0; i < objects.size(); i++) {

					shader->setUniform1i("_texture", objects[i]->getTID());
					m_renderer->submit(objects[i]);
				}

				shader->disable();
				skybox->render(m_projection, camera.getViewMatrix());
			}
		}

		void EnvironmentMap::stop() {

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, m_windowDimension.width, m_windowDimension.height);
		}
	}
}
