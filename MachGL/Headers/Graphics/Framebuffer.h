/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		enum class ColorDepth {

			MACH_8_BIT, MACH_16_BIT, MACH_32_BIT
		};

		class Framebuffer {

			private:
				GLuint m_fbo = 0;
				std::vector<GLuint> m_textureColorBuffers;
				GLuint m_textureDepthbuffer = 0;
				GLuint m_rbo = 0;
				float m_width = 0;
				float m_height = 0;
				ColorDepth m_colorDepth = ColorDepth::MACH_8_BIT;
				uint32_t m_attachments = 1;
				uint32_t m_framebuffers = 1;

			public:
				/// <summary>
				/// Default constructor for Framebuffer, not recommended for use.
				/// </summary>
				Framebuffer() = default;

				/// <summary>
				/// Creates a Framebuffer of specified width and height in pixels.
				/// </summary>
				/// <param name="width">Horizontal resolution of the Framebuffer.</param>
				/// <param name="height">Vertical resolution of the Framebuffe.r</param>
				Framebuffer(const float& width, const float& height);

				/// <summary>
				/// Starts the Framebuffer capture, this function should be called in the render loop before rendering the Framebuffer content.
				/// </summary>
				virtual void capture();

				/// <summary>
				/// Stops the capture of the Framebuffer, this function should be called at the end of the render loop after rendering the Framebuffer content.
				/// </summary>
				virtual void stop();

				inline const GLuint& getColorTexture() const { return m_textureColorBuffers[0]; }
				
				//inline const GLuint& getColorTexture1() const { return m_textureColorBuffers[1]; }

				/// <summary>
				/// Gets the textureID for the Framebuffer depth texture. 
				/// </summary>
				/// <returns>Depth textureID.</returns>
				inline const GLuint& getDepthTexture() const { return m_textureDepthbuffer; }

				inline void setColorDepth(const ColorDepth& colorDepth) { m_colorDepth = colorDepth; }

				void setAttachments(const uint32_t& attachments);
				
				void init();

			private:
				void switchColorDepth();
				void textureParameters();
				void generateRenderbuffer();
				void generateDepthbuffer();
		};
	}
}
