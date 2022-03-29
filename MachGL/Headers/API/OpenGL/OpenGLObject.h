/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Object/Object.h"

namespace MachGL {
    namespace Object {

        class OpenGLObject : public Object {
            
            public:
                OpenGLObject();
                OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image);
                OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const ObjectType& type);
                OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2, const ObjectType& type);
                void destroy() override;
            
            protected:
                void loadToBuffers() override;
                void loadToVAO() override;
        };
    }
}
