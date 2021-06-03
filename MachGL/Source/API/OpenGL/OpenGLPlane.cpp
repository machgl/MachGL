/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLPlane.h"

namespace MachGL {
    namespace Plane {
    
        OpenGLPlane::OpenGLPlane(const PlaneProperties& properties) {
            
            m_position = properties.position;
            m_size = properties.size;
            m_color = properties.color;
            m_image = properties.image;
            m_shape = properties.shape;
            m_type = properties.type;

            loadToVAO();
        }

        OpenGLPlane::OpenGLPlane(const std::vector<float3>& vertices, const std::vector<unsigned short>& indices, const std::vector<float2>& uvs, const PlaneProperties& properties) {
            
            m_vertices = vertices;
            m_indices = indices;
            m_UVs = uvs;
            m_position = properties.position;
            m_size = properties.size;
            m_color = properties.color;
            m_image = properties.image;
            m_shape = properties.shape;
            m_type = properties.type;
            loadToVAO();
        }

        OpenGLPlane::OpenGLPlane(const float3& position, const float2& size, const GLuint& texture) {
            
            m_position = position;
            m_size = size;
            m_texture = texture;
            m_shape = PlaneShape::QUAD;
            m_color = float4();
            m_type = PlaneType::DYNAMIC;
            loadToVAO();
        }
    
        void OpenGLPlane::loadToVAO() {

            switch (m_shape) {

                case PlaneShape::QUAD:
                    m_vertices = m_quadVertices;
                    m_indices = m_quadIndices;
                    m_UVs = m_quadUVs;
                    break;
                case PlaneShape::TRIANGLE:
                    m_vertices = m_triVertices;
                    m_indices = m_triIndices;
                    m_UVs = m_triUVs;
                case PlaneShape::CUSTOM:
                    break;
                default:
                    break;
            }

            uint32_t vertex_index = 0;
            uint32_t UV_index = 1;
            uint32_t TID_index = 2;
            uint32_t color_index = 3;
            
            uint32_t vertexSize = sizeof(Vertex);
            uint32_t vertexBufferSize = (uint32_t)m_vertices.size() * vertexSize;
            uint32_t indexBufferSize = (uint32_t)m_indices.size() * sizeof(Index);

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_IBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

            glEnableVertexAttribArray(vertex_index);
            glEnableVertexAttribArray(UV_index);
            glEnableVertexAttribArray(TID_index);
            glEnableVertexAttribArray(color_index);

            glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)0);
            glVertexAttribPointer(UV_index, 2, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, uv)));
            glVertexAttribPointer(TID_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, tid)));
            glVertexAttribPointer(color_index, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize, (const GLvoid*)(offsetof(Vertex, color)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindVertexArray(0);
        }

        void OpenGLPlane::loadToBuffers() {

            glBindBuffer(GL_ARRAY_BUFFER, getVBO());
            m_vertexBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            auto& vertices = this->getVertices();
            auto& indices = this->getIndices();
            auto& uvs = this->getUVs();
            auto& position = this->getPosition();
            auto& size = this->getSize();
            auto& color = this->getColor();
            auto tid = this->getTID();

            uint32_t c = 0;

            float r = color.x * 255.0f;
            float g = color.y * 255.0f;
            float b = color.z * 255.0f;
            float a = color.x * 255.0f;

            c = (uint32_t)a << 24 | (uint32_t)b << 16 | (uint32_t)g << 8 | (uint32_t)r;

            for (uint32_t i = 0; i < vertices.size(); i++) {

                m_vertexBuffer->vertex = (vertices[i] * float3(size.x, size.y, 0)) + position;
                m_vertexBuffer->uv = uvs[i];
                if (tid != 0)m_vertexBuffer->tid = (float)tid + 1;
                m_vertexBuffer->color = c;
                m_vertexBuffer++;
            }

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIBO());
            m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

            for (uint32_t i = 0; i < indices.size(); i++) {

                m_indexBuffer->index = indices[i];
                m_indexBuffer++;
            }

            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    
        void OpenGLPlane::destroy() {

            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_IBO);
            glDeleteVertexArrays(1, &m_VBO);

            delete m_vertexBuffer;
            delete m_indexBuffer;
        }
    }
}
