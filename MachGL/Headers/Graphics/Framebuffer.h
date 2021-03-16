/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		class Framebuffer {

			private:
				GLuint m_fbo = 0;
				GLuint m_textureColorBuffer = 0;
				GLuint m_textureDepthBuffer = 0;
				GLuint m_rbo = 0;
				float m_width = 0;
				float m_height = 0;

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
