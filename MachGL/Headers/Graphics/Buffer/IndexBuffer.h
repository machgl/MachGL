#pragma once

#include "../../Core/Includes.h"

namespace MachGL {
    namespace Graphics {

        class IndexBuffer {

        private:
            GLuint m_bufferID;
            GLuint m_count;

        public:
            IndexBuffer(GLushort* data, const GLsizei& count);
            ~IndexBuffer();
            void bind() const;
            void unbind() const;
            inline GLuint getCount() const { return m_count; }
        };
    }
}

