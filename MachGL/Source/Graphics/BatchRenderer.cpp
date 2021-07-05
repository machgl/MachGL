/*
 
    MachGL (Alpha)
 
 */

#include "../../Headers/Graphics/BatchRenderer.h"
#include "../../Headers/API/OpenGL/OpenGLBatchRenderer.h"

namespace MachGL {
    namespace Graphics {
    
        Sprite::Sprite(const float2& position, const float2& size, const MACH_IMAGE& texture, const float4& color) {
            
            m_position = position;
            m_size = size;
            m_texture = texture;
            m_color = color;
        }

        void Sprite::translate(const matrix4x4& translationMatrix) {
            
            m_translationMatrix = translationMatrix;
        }
    
        MACH_BATCH_RENDERER BatchRenderer::createBatchRenderer() {
            
            switch (MACH_GRAPHICS_API) {
                
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLBatchRenderer>();
                default: return make_sPoint<OpenGLBatchRenderer>();
            }
        }
    
        void BatchRenderer::setShader(const MACH_SHADER& shader) {
                
            m_shader = shader;
        }
    
        void BatchRenderer::submit(const std::vector<Sprite>& sprites) {
            
            m_sprites = sprites;
            flush();
        }
    }
}
