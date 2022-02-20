/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/Plane.h"
#include "../../Headers/API/OpenGL/OpenGLPlane.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Plane {

        MACH_PLANE Plane::createPlane(const PlaneProperties& properties) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLPlane>(properties);
                default: return make_sPoint<OpenGLPlane>(properties);
            }
        }
    
        MACH_PLANE Plane::createPlane(const std::vector<float3>& vertices, const std::vector<unsigned short>& indices, const std::vector<float2>& uvs, const PlaneProperties& properties) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLPlane>(vertices, indices, uvs, properties);
                default: return make_sPoint<OpenGLPlane>(vertices, indices, uvs, properties);
            }
        }
    
        MACH_PLANE Plane::createPlane(const float3& position, const float2& size, const GLuint& texture) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLPlane>(position, size, texture);
                default: return make_sPoint<OpenGLPlane>(position, size, texture);
            }
        }
    
        void Plane::create() { loadToBuffers(); }
	}
}
