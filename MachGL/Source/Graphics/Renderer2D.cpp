/*
 
    MachGL (Alpha)
 
 */

#include "../../Headers/Graphics/Renderer2D.h"
#include "../../Headers/API/OpenGL/OpenGLRenderer2D.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Graphics {

        MACH_RENDERER_2D Renderer2D::createRenderer() {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLRenderer2D>();
                default: return make_sPoint<OpenGLRenderer2D>();
            }
        }
    
        void Renderer2D::submit(const std::vector<Plane::MACH_PLANE>& planes) {

            for (uint32_t i = 0; i < planes.size(); i++) {

                flush(planes[i]);
            }
        }

        void Renderer2D::submit(const Plane::MACH_PLANE& plane) { flush(plane); }
	}
}
