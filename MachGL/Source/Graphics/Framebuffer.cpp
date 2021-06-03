/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/Framebuffer.h"
#include "../../Headers/API/OpenGL/OpenGLFramebuffer.h"

namespace MachGL {
	namespace Graphics {
        
        MACH_FRAMEBUFFER Framebuffer::createFramebuffer(const float& width, const float& height) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLFramebuffer>(width, height);
                default: return make_sPoint<OpenGLFramebuffer>(width, height);
            }
        }

		void Framebuffer::setAttachments(const uint32_t& attachments) {

			if (attachments < 1) m_attachments = 1;
			if (attachments > 2) m_attachments = 2;
			m_attachments = attachments;
		}
	}
}
