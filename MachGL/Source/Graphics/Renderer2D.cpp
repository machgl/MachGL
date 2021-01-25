#include "../../Headers/Graphics/Renderer2D.h"

namespace MachGL {
	namespace Graphics {
        
		Renderer2D::Renderer2D() {
    
            init();
		}

        Renderer2D::~Renderer2D() {

            delete m_IBO;
        }

		void Renderer2D::init() {

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_UV_INDEX);
            glEnableVertexAttribArray(SHADER_TID_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, uv)));
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, tid)));
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, color)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            int offset = 0;
            for (int i = 0; i < RENDERER_INDICIES_SIZE; i += 6) {

                m_indicies[i] = offset + 0;
                m_indicies[i + 1] = offset + 1;
                m_indicies[i + 2] = offset + 2;
                m_indicies[i + 3] = offset + 2;
                m_indicies[i + 4] = offset + 3;
                m_indicies[i + 5] = offset + 0;

                offset += 4;
            }

            m_IBO = new IndexBuffer(m_indicies, RENDERER_INDICIES_SIZE);

            glBindVertexArray(0);
		}

        void Renderer2D::begin() {

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void Renderer2D::submit(Plane* plane) {

            const float3& position = plane->getPosition();
            const float2& size = plane->getSize();
            const std::vector<float2>& uvs = plane->getUVs();
            const GLuint tid = plane->getTID();
            const float4& color = plane->getColor();

            unsigned int c = 0;

            float ts = 0.0f;

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

                        end();
                        flush();
                        begin();
                    }

                    m_textureSlots.push_back(tid);
                    ts = (float)(m_textureSlots.size());
                }

            }  else {

                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.x * 255.0f;

                c = a << 24 | b << 16 | g << 8 | r;
            }

            m_buffer->vertex = position;
            m_buffer->uv = uvs[0];
            m_buffer->tid = ts;
            m_buffer->color = c;
            m_buffer++;

            m_buffer->vertex = float3(position.x, position.y + size.y, position.z);
            m_buffer->uv = uvs[1];
            m_buffer->tid = ts;
            m_buffer->color = c;
            m_buffer++;

            m_buffer->vertex = float3(position.x + size.x, position.y + size.y, position.z);
            m_buffer->uv = uvs[2];
            m_buffer->tid = ts;
            m_buffer->color =c;
            m_buffer++;

            m_buffer->vertex = float3(position.x + size.x, position.y, position.z);
            m_buffer->uv = uvs[3];
            m_buffer->tid = ts;
            m_buffer->color = c;
            m_buffer++;

            m_indexCount += 6;
        }

        void Renderer2D::flush() {

            for (int i = 0; i < m_textureSlots.size(); i++) {

                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
            }

            glBindVertexArray(m_VAO);
            m_IBO->bind();

            glDrawElements(GL_TRIANGLES, m_IBO->getCount(), GL_UNSIGNED_SHORT, NULL);

            m_IBO->unbind();
            glBindVertexArray(0);

            m_indexCount = 0;
        }

        void Renderer2D::end() {

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
	}
}