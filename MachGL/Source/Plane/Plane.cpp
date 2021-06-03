/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/Plane.h"
#include "../../Headers/API/OpenGL/OpenGLPlane.h"

namespace MachGL {
	namespace Plane {

        MACH_PLANE Plane::createPlane(const PlaneProperties& properties) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLPlane>(properties);
                default: return make_sPoint<OpenGLPlane>(properties);
            }
        }
    
        MACH_PLANE Plane::createPlane(const std::vector<float3>& vertices, const std::vector<unsigned short>& indices, const std::vector<float2>& uvs, const PlaneProperties& properties) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLPlane>(vertices, indices, uvs, properties);
                default: return make_sPoint<OpenGLPlane>(vertices, indices, uvs, properties);
            }
        }
    
        MACH_PLANE Plane::createPlane(const float3& position, const float2& size, const GLuint& texture) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLPlane>(position, size, texture);
                default: return make_sPoint<OpenGLPlane>(position, size, texture);
            }
        }
    
        void Plane::create() { loadToBuffers(); }
	}
}
