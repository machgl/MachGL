/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/Framebuffer.h"

namespace MachGL {
	namespace Graphics {

		Framebuffer::Framebuffer(const float& width, const float& height)
			:m_width(width), m_height(height) { }

		void Framebuffer::init() {

			for (uint32_t i = 0; i < m_attachments; i++) m_textureColorBuffers.push_back(0);

			glGenFramebuffers(1, &m_fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
					
			for (uint32_t i = 0; i < m_attachments; i++) {

				glGenTextures(m_attachments, &m_textureColorBuffers[i]);
				glBindTexture(GL_TEXTURE_2D, m_textureColorBuffers[i]);
				switchColorDepth();
				textureParameters();
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textureColorBuffers[i], 0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
						
			generateRenderbuffer();

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				MACH_ERROR_MSG("Framebuffer is not complete");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::switchColorDepth() {

			switch (m_colorDepth) {

				case(ColorDepth::MACH_8_BIT):
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)m_width, (GLsizei)m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					break;

				case(ColorDepth::MACH_16_BIT):
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, (GLsizei)m_width, (GLsizei)m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					break;

				case(ColorDepth::MACH_32_BIT):
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, (GLsizei)m_width, (GLsizei)m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					break;

				default:
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)m_width, (GLsizei)m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					break;
			}
		}

		void Framebuffer::setAttachments(const uint32_t& attachments) {

			if (attachments < 1) m_attachments = 1;
			if (attachments > 2) m_attachments = 2;
			m_attachments = attachments;
		}

		void Framebuffer::generateRenderbuffer() {

			glGenRenderbuffers(1, &m_rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, (GLsizei)m_width, (GLsizei)m_height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
		}

		void Framebuffer::textureParameters() {

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		void Framebuffer::generateDepthbuffer() {

			glGenTextures(1, &m_textureDepthbuffer);
			glBindTexture(GL_TEXTURE_2D, m_textureDepthbuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (GLsizei)m_width, (GLsizei)m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			textureParameters();
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_textureDepthbuffer, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Framebuffer::capture() {

			glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Framebuffer::stop() {

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}
