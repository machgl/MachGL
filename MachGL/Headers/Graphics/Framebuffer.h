/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		enum class ColorDepth {

			MACH_8_BIT, MACH_16_BIT, MACH_32_BIT
		};

		class Framebuffer {

			protected:
				uint32_t			  m_fbo = 0;
				std::vector<uint32_t> m_textureColorBuffers;
				uint32_t			  m_textureDepthbuffer = 0;
				uint32_t			  m_rbo = 0;
				float				  m_width = 0;
				float				  m_height = 0;
				ColorDepth			  m_colorDepth = ColorDepth::MACH_8_BIT;
				uint32_t			  m_attachments = 1;
				uint32_t			  m_framebuffers = 1;

			public:
                
                static sPoint<Framebuffer> createFramebuffer(const float& width, const float& height);
            
				/// <summary>
				/// Default constructor for Framebuffer, not recommended for use.
				/// </summary>
				Framebuffer() = default;
                ~Framebuffer() = default;

				/// <summary>
				/// Starts the Framebuffer capture, this function should be called in the render loop before rendering the Framebuffer content.
				/// </summary>
				virtual void capture() = 0;

				/// <summary>
				/// Stops the capture of the Framebuffer, this function should be called at the end of the render loop after rendering the Framebuffer content.
				/// </summary>
				virtual void stop() = 0;

				inline const uint32_t& getColorTexture() const { return m_textureColorBuffers[0]; }
				
				//inline const GLuint& getColorTexture1() const { return m_textureColorBuffers[1]; }

				/// <summary>
				/// Gets the textureID for the Framebuffer depth texture. 
				/// </summary>
				/// <returns>Depth textureID.</returns>
				inline const uint32_t& getDepthTexture() const { return m_textureDepthbuffer; }

				inline void setColorDepth(const ColorDepth& colorDepth) { m_colorDepth = colorDepth; }

				void setAttachments(const uint32_t& attachments);
				
				virtual void init() = 0;
            protected:
                virtual void switchColorDepth() = 0;
                virtual void textureParameters() = 0;
                virtual void generateRenderbuffer() = 0;
                virtual void generateDepthbuffer() = 0;
		};
    
        using MACH_FRAMEBUFFER = sPoint<Framebuffer>;
	}
}
