/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "Renderer2D.h"

namespace MachGL {
	namespace Graphics {

		class Framebuffer {

			private:
				GLuint m_fbo;
				GLuint m_textureColorBuffer;
				GLuint m_textureDepthBuffer;
				GLuint m_rbo;
				float m_width;
				float m_height;

			public:
				Framebuffer() = default;
				Framebuffer(const float& width, const float& height);
				void capture();
				void stop();
				inline const GLuint& getColorTexture() const { return m_textureColorBuffer; }
				inline const GLuint& getDepthTexture() const { return m_textureDepthBuffer; }
			private:
				void init();
		};
	}
}
