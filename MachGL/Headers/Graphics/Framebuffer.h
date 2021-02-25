/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
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
				void capture();

				/// <summary>
				/// Stops the capture of the Framebuffer, this function should be called at the end of the render loop after rendering the Framebuffer content.
				/// </summary>
				void stop();

				/// <summary>
				/// Gets the textureID for the Framebuffer RGB texture.
				/// </summary>
				/// <returns>RGB textureID.</returns>
				inline const GLuint& getColorTexture() const { return m_textureColorBuffer; }

				/// <summary>
				/// Gets the textureID for the Framebuffer depth texture. 
				/// </summary>
				/// <returns>Depth textureID.</returns>
				inline const GLuint& getDepthTexture() const { return m_textureDepthBuffer; }
			private:
				void init();
		};
	}
}
