#pragma once

#include "Buffer.h"

namespace MachGL {
	namespace Graphics {

        Buffer::Buffer(GLfloat* data, const GLsizei& count, const GLuint& componentCount)
            : m_componentCount(componentCount) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        
        Buffer::Buffer(GLuint* data, const GLsizei& count, const GLuint& componentCount)
            : m_componentCount(componentCount) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        Buffer::~Buffer() {

            glDeleteBuffers(1, &m_bufferID);
        }

        void Buffer::bind() const {

            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        }

        void Buffer::unbind() const {

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
	}
}