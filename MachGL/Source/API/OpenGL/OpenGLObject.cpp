/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLObject.h"

namespace MachGL {
    namespace Object {

        OpenGLObject::OpenGLObject() {
            
            m_position = float3();
            m_type = ObjectType::MESH;
            m_VAO = 0;
            m_IBO = 0;
            m_VBO = 0;
            m_TID = 0;
            m_model = NULL;
        }
    
        OpenGLObject::OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image) {
        
            m_model = model;
            m_position = position;
            m_image = image;
            m_type = ObjectType::MESH;
            loadToVAO();
            generateCubeBounds();
        }

        OpenGLObject::OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const ObjectType& type) {

            m_model = model;
            m_position = position;
            m_image = image;
            m_type = type;
            loadToVAO();
            generateCubeBounds();
        }

        OpenGLObject::OpenGLObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2, const ObjectType& type) {
         
            m_model = model;
            m_position = position;
            m_image = image;
            m_image2 = image2;
            m_type = type;
            loadToVAO();
            generateCubeBounds();
            if (m_image2 != nullptr)
                m_dynamicSkybox = true;
        }
    
        void OpenGLObject::loadToVAO() {

            uint32_t vertex_index = 0;
            uint32_t uv_index = 1;
            uint32_t tid_index = 2;
            uint32_t normal_index = 3;
            uint32_t color_index = 4;
            uint32_t shine_index = 5;
            uint32_t reflectivity_index = 6;
            uint32_t texture_scale_index = 7;

            uint32_t vertexSize = sizeof(Vertex);
            uint32_t vertexBufferSize = (uint32_t)m_model->getVertexSize() * vertexSize;
            uint32_t indexBufferSize = (uint32_t)m_model->getIndexSize() * sizeof(Index);

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_IBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

            glEnableVertexAttribArray(vertex_index);
            glEnableVertexAttribArray(uv_index);
            glEnableVertexAttribArray(tid_index);
            glEnableVertexAttribArray(normal_index);
            glEnableVertexAttribArray(color_index);
            glEnableVertexAttribArray(shine_index);
            glEnableVertexAttribArray(reflectivity_index);
            glEnableVertexAttribArray(texture_scale_index);

            glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)0);
            glVertexAttribPointer(uv_index, 2, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, uv)));
            glVertexAttribPointer(tid_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, tid)));
            glVertexAttribPointer(normal_index, 3, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, normal)));
            glVertexAttribPointer(color_index, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize, (const GLvoid*)(offsetof(Vertex, color)));
            glVertexAttribPointer(shine_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, shine)));
            glVertexAttribPointer(reflectivity_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, reflectivity)));
            glVertexAttribPointer(texture_scale_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, textureScale)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindVertexArray(0);
        }

        void OpenGLObject::loadToBuffers() {

            glBindBuffer(GL_ARRAY_BUFFER, getVBO());
            m_vertexBuffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            auto& vertices = this->getModel()->getVertices();
            auto& UVs = this->getModel()->getUVs();
            auto& normals = this->getModel()->getNormals();
            auto& indices = this->getModel()->getIndices();
            auto& reflectivity = this->getReflectivity();
            auto& color = this->getColor();
            auto tid = this->getTID();
            auto& scale = this->getScale();
            auto& position = this->getPosition();
            auto& shineDamper = this->getShineDamper();
            auto& textureScale = this->getTextureScale();

            float r = color.x * 255.0f;
            float g = color.y * 255.0f;
            float b = color.z * 255.0f;
            float a = color.w * 255.0f;

            uint32_t c = (uint32_t)a << 24 | (uint32_t)b << 16 | (uint32_t)g << 8 | (uint32_t)r;

            if (m_type == ObjectType::SKYBOX) {

                for (uint32_t i = 0; i < vertices.size(); i++) {

                    m_vertexBuffer->vertex = (vertices[i] * scale) + position;
                    m_vertexBuffer++;
                }
            }
            else {

                for (uint32_t i = 0; i < vertices.size(); i++) {

                    m_vertexBuffer->vertex = (vertices[i] * scale) + position;

                    if (this->getModel()->hasTexture())
                        m_vertexBuffer->uv = UVs[i];
                    
                    m_vertexBuffer->normal = normals[i];
                    if (tid != 0) m_vertexBuffer->tid = (float)tid + 1;
                    m_vertexBuffer->color = c;
                    m_vertexBuffer->shine = shineDamper;
                    m_vertexBuffer->reflectivity = reflectivity;
                    m_vertexBuffer->textureScale = textureScale;
                    m_vertexBuffer++;
                }
            }

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            if (m_type != ObjectType::SKYBOX) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIBO());
                m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

                for (uint32_t i = 0; i < indices.size(); i++) {

                    m_indexBuffer->index = indices[i];
                    m_indexBuffer++;
                }

                glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }
    
        void OpenGLObject::destroy() {

            if (this->getType() != ObjectType::SKYBOX) glDeleteBuffers(1, &m_IBO);

            glDeleteBuffers(1, &m_VBO);
            glDeleteVertexArrays(1, &m_VAO);

            delete m_vertexBuffer;
            delete m_indexBuffer;
            delete m_bounds;
        }
    }
}
