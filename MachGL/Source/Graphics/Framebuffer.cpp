/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/Framebuffer.h"
#include "../../Headers/API/OpenGL/OpenGLFramebuffer.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Graphics {
        
        MACH_FRAMEBUFFER Framebuffer::createFramebuffer(const float& width, const float& height) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLFramebuffer>(width, height);
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
