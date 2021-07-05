/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLBatchRenderer.h"

namespace MachGL {
    namespace Graphics {
        
        OpenGLBatchRenderer::OpenGLBatchRenderer() { init(); }
    
        void OpenGLBatchRenderer::init() {
            
            uint32_t vertex_index = 0;
            uint32_t UV_index = 1;
            uint32_t TID_index = 2;
            uint32_t color_index = 3;
            
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_IBO);
            
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            
            glEnableVertexAttribArray(vertex_index);
            glEnableVertexAttribArray(UV_index);
            glEnableVertexAttribArray(TID_index);
            glEnableVertexAttribArray(color_index);
            
            glBufferData(GL_ARRAY_BUFFER, m_vertexBufferSize, NULL, GL_DYNAMIC_DRAW);
            
            glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, m_vertexSize, (const GLvoid*)0);
            glVertexAttribPointer(UV_index, 2, GL_FLOAT, GL_FALSE, m_vertexSize, (const GLvoid*)(offsetof(Vertex, uv)));
            glVertexAttribPointer(TID_index, 1, GL_FLOAT, GL_FALSE, m_vertexSize, (const GLvoid*)(offsetof(Vertex, tid)));
            glVertexAttribPointer(color_index, 4, GL_UNSIGNED_BYTE, GL_TRUE, m_vertexSize, (const GLvoid*)(offsetof(Vertex, color)));
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            uint32_t offset = 0;
            
            for (uint32_t i = 0; i < m_maxQuads * 6; i += 6) {
            
                m_indices[i + 0] = 0 + offset;
                m_indices[i + 1] = 1 + offset;
                m_indices[i + 2] = 2 + offset;
                
                m_indices[i + 3] = 2 + offset;
                m_indices[i + 4] = 3 + offset;
                m_indices[i + 5] = 0 + offset;
                
                offset += 4;
            }
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferSize, NULL, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    
        void OpenGLBatchRenderer::begin() {
            
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_vertexBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        }
    
        void OpenGLBatchRenderer::push() {
            
            for (uint32_t i = 0; i < m_sprites.size(); i++) {
                
                for (uint32_t j = 0; j < 4; j++) {
                    
                    uint32_t r = m_sprites[i].m_color.x * 255;
                    uint32_t g = m_sprites[i].m_color.y * 255;
                    uint32_t b = m_sprites[i].m_color.z * 255;
                    uint32_t a = m_sprites[i].m_color.w * 255;
                    
                    uint32_t col = a << 24 | b << 16 | g << 8 | r;
                    
                    m_vertexBuffer->vertex = m_quadVertices[j];
                    m_vertexBuffer->uv = m_quadUVs[j];
                    if (m_sprites[i].m_texture->getTID() != 0)
                        m_vertexBuffer->tid = m_sprites[i].m_texture->getTID() + 1;
                    m_vertexBuffer->color = col;
                    m_vertexBuffer++;
                }
                
                m_shader->enable();
                m_shader->setUniformMatrix4fv("_batch_translationMatrix", m_sprites[i].m_translationMatrix);
            }

            for (uint32_t i = 0; m_maxQuads * 6; i++) {
                
                m_indexBuffer->index = m_indices[i];
                m_indexBuffer++;
            }
        }
        
        void OpenGLBatchRenderer::end() {
            
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    
        void OpenGLBatchRenderer::flush() {
            
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
            
            m_shader->disable();
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    
        void OpenGLBatchRenderer::destroy() {
            
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_IBO);
            
            delete m_vertexBuffer;
            delete m_indexBuffer;
        }
    }
}
