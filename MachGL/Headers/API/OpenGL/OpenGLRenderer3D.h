/*
 
    MachGL (Alpha)
 
 */

#include "../../Graphics/Renderer3D.h"

namespace MachGL {
    namespace Graphics {

        class OpenGLRenderer3D : public Renderer3D {
            
            public:
                OpenGLRenderer3D() = default;
                ~OpenGLRenderer3D() = default;
            protected:
                void flush(const Object::MACH_OBJECT& object) override;
        };
    }
}
