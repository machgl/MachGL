#pragma once

#include "IndexBuffer.h"

namespace MachGL {
    namespace Graphics {

        IndexBuffer::IndexBuffer(GLushort* data, const GLsizei& count)
            : m_count(count) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::~IndexBuffer() {

            glDeleteBuffers(1, &m_bufferID);
        }

        void IndexBuffer::bind() const {

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        }

        void IndexBuffer::unbind() const {

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}