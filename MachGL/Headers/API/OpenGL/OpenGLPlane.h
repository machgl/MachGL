/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Plane/Plane.h"

namespace MachGL {
    namespace Plane {

        class OpenGLPlane : public Plane {
                
            public:
                OpenGLPlane() = default;
                ~OpenGLPlane() = default;
                OpenGLPlane(const PlaneProperties& properties);
                OpenGLPlane(const std::vector<float3>& vertices, const std::vector<unsigned short>& indices, const std::vector<float2>& uvs, const PlaneProperties& properties);
                OpenGLPlane(const float3& position, const float2& size, const GLuint& texture);
                void destroy() override;
            
            protected:
                void loadToVAO() override;
                void loadToBuffers() override;
        };
    }
}
