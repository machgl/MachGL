/*
    
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Graphics/Renderer2D.h"

namespace MachGL {
    namespace Graphics {

        class OpenGLRenderer2D : public Renderer2D {
            
            public:
                OpenGLRenderer2D() = default;
                ~OpenGLRenderer2D() = default;
            protected:
                void flush(const Plane::MACH_PLANE& plane) override;
        };
    }
}
