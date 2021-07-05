/*
 
    MachGL (Alpha)
 
 */

#include "../../Graphics/BatchRenderer.h"

namespace MachGL {
    namespace Graphics {

        class OpenGLBatchRenderer : public BatchRenderer {
            
            private:
                Vertex* m_vertexBuffer;
                Index* m_indexBuffer;
                uint32_t m_VAO;
                uint32_t m_VBO;
                uint32_t m_IBO;
            
            public:
                OpenGLBatchRenderer();
                void destroy() override;
            
            protected:
                void begin() override;
                void push() override;
                void end() override;
                void flush() override;
            
            private:
                void init();
        };
    }
}
