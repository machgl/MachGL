#include "../../Headers/Graphics/Renderer2D.h"

namespace MachGL {
	namespace Graphics {

        Renderer2D::~Renderer2D() {

            delete m_buffer;
            delete m_indexBuffer;
        }

        void Renderer2D::begin(const Plane& plane) {

            glBindBuffer(GL_ARRAY_BUFFER, plane.getVBO());
            m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.getIBO());
            m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void Renderer2D::submit(const std::vector<Plane>& planes) {

            for (int i = 0; i < planes.size(); i++) {

                render(planes[i]);
            }
        }

        void Renderer2D::end(const Plane& plane) {

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void Renderer2D::flush(const Plane& plane) {

            glBindVertexArray(plane.getVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.getIBO());

            glDrawElements(GL_TRIANGLES, plane.getIndices().size(), GL_UNSIGNED_SHORT, NULL);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void Renderer2D::render(const Plane& plane) {

            begin(plane);

            const std::vector<float3>& vertices = plane.getVertices();
            const std::vector<GLushort>& indices = plane.getIndices();
            const std::vector<float2>& uvs = plane.getUVs();
            const float3& position = plane.getPosition();
            const float2& size = plane.getSize();
            const float4& color = plane.getColor();

            float ts = 0.0f;
            unsigned int c = 0;

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.x * 255.0f;

            c = a << 24 | b << 16 | g << 8 | r;

            const GLuint tid = plane.getTID();

            if (tid > 0) {

                bool found = false;

                for (int i = 0; i < m_textureSlots.size(); i++) {

                    if (m_textureSlots[i] == tid) {

                        ts = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if (!found) {

                    if (m_textureSlots.size() >= 32) {

                        end(plane);
                        flush(plane);
                        begin(plane);
                    }

                    m_textureSlots.push_back(tid);
                    ts = (float)(m_textureSlots.size());
                }
            }

            for (int i = 0; i < vertices.size(); i++) {

                m_buffer->vertex = (vertices[i] * float3(size.x, size.y, 0)) + position;
                m_buffer->uv = uvs[i];
                m_buffer->tid = ts;
                m_buffer->color = c;
                m_buffer++;
            }

            for (int i = 0; i < indices.size(); i++) {

                m_indexBuffer->index = indices[i];
                m_indexBuffer++;
            }

            end(plane);

            for (int i = 0; i < m_textureSlots.size(); i++) {

                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
            }

            flush(plane);
        }
	}
}