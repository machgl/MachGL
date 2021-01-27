#include "../../../Headers/Graphics/Buffer/VertexArray.h"

namespace MachGL {
	namespace Graphics {

        VertexArray::VertexArray() {

            glGenVertexArrays(1, &m_arrayID);
        }

        VertexArray::~VertexArray() {

            for (int i = 0; i < m_buffers.size(); i++) {

                delete m_buffers[i];
            }

            glDeleteVertexArrays(1, &m_arrayID);
        }

        void VertexArray::addBuffer(Buffer* buffer, const GLuint& index) {

            bind();
            buffer->bind();

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();
        }

        void VertexArray::bind() const {

            glBindVertexArray(m_arrayID);
        }

        void VertexArray::unbind() const {

            glBindVertexArray(0);
        }
	}
}