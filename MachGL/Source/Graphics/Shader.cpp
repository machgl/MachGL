#include "../../Headers/Graphics/Shader.h"
#include "../../Headers/API/OpenGL/OpenGLShader.h"


namespace MachGL {
    namespace Graphics {

        MACH_SHADER Shader::createShader(const std::string& vertexPath, const std::string& fragmentPath) {
            
            switch (MACH_GRAPHICS_API) {
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLShader>(vertexPath, fragmentPath);
                default: return make_sPoint<OpenGLShader>(vertexPath, fragmentPath);
            }
        }
        
        bool Shader::inCache() const {

            if (shaderCache.size() > 0)
                for (uint32_t i = 0; i < shaderCache.size(); i++) if (shaderCache[i].id == m_shaderID) return true;

            return false;
        }
    }
}
