/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Graphics/Framebuffer.h"

namespace MachGL {
    namespace Graphics {
    
        class OpenGLFramebuffer : public Framebuffer {
        
            public:
                OpenGLFramebuffer(const float& width, const float& height);
                void init() override;
                void capture() override;
                void stop() override;
                
            private:
                void switchColorDepth() override;
                void textureParameters() override;
                void generateRenderbuffer() override;
                void generateDepthbuffer() override;
        };
    }
}
