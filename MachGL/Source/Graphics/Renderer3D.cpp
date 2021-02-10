#include "../../Headers/Graphics/Renderer3D.h"

namespace MachGL {
    namespace Graphics {

        typedef Object::ObjectType type;

        Renderer3D::~Renderer3D() {

            delete m_buffer;
            delete m_indexBuffer;
        }

        void Renderer3D::begin(const Object::Object& object){

            glBindBuffer(GL_ARRAY_BUFFER, object.getVBO());
            m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.getIBO());
                m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
            }
        }

        void Renderer3D::submit(const std::vector<Object::Object>& objects) {

            for (int i = 0; i < objects.size(); i++) {

                switch (objects[i].getType()) {

                    case type::SKYBOX:
                        if (objects[i].isDynamicSkybox())
                            renderDynamicSkybox(objects[i]);
                        else
                            renderSkybox(objects[i]);
                        break;

                    case type::TERRAIN:
                        renderTerrain(objects[i]);
                        break;
                    
                    default:
                        renderMesh(objects[i]);
                        break;
                }
            }
        }

        void Renderer3D::submit(const std::vector<Object::Object>& objects, const Object::Camera& camera, const float& renderDistance) {

            for (int i = 0; i < objects.size(); i++) {
                switch (objects[i].getType()) {

                    case type::SKYBOX:
                        if (objects[i].isDynamicSkybox())
                            renderDynamicSkybox(objects[i]);
                        else
                            renderSkybox(objects[i]);
                        break;

                    case type::TERRAIN:
                        renderTerrain(objects[i]);
                        break;

                    default:
                        if (Maths::Vector::distance(camera.getPosition(), objects[i].getPosition()) <= renderDistance)
                            renderMesh(objects[i]);
                        break;
                }
            }
        }

        void Renderer3D::end(const Object::Object& object) {

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }

        void Renderer3D::flush(const Object::Object& object) {

            glBindVertexArray(object.getVAO());
            
            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.getIBO());
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);
            }

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN)
                glDrawElements(GL_TRIANGLES, object.getModel()->getIndexSize(), GL_UNSIGNED_SHORT, NULL);

            if (object.getType() == type::SKYBOX)
                glDrawArrays(GL_TRIANGLES, 0, object.getModel()->getVertices().size());

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glDisable(GL_CULL_FACE);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindVertexArray(0);
        }

        void Renderer3D::renderMesh(const Object::Object& object) {

            begin(object);

            const std::vector<float3>& vertices = object.getModel()->getVertices();
            const float3& scale = object.getScale();
            const std::vector<float2>& UVs = object.getModel()->getUVs();
            const std::vector<float3>& normals = object.getModel()->getNormals();
            const float3& position = object.getPosition();
            const std::vector<GLushort>& indices = object.getModel()->getIndices();
            const float& shineDamper = object.getShineDamper();
            const float& reflectivity = object.getReflectivity();
            const float4& color = object.getColor();
            const GLuint tid = object.getTID();
            const float& textureScale = object.getTextureScale();

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

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

                        end(object);
                        begin(object);
                    }

                    m_textureSlots.push_back(tid);
                    ts = (float)(m_textureSlots.size());
                }

            }
            else {

                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.x * 255.0f;

                c = a << 24 | b << 16 | g << 8 | r;
            }

            for (int i = 0; i < vertices.size(); i++) {

                m_buffer->vertex = (vertices[i] * scale) + position;

                if (UVs.size() > 0) {

                    m_buffer->uv = UVs[i];
                }
                m_buffer->tid = ts;
                m_buffer->normal = normals[i];
                m_buffer->color = c;
                m_buffer->shine = shineDamper;
                m_buffer->reflectivity = reflectivity;
                m_buffer->textureScale = textureScale;
                m_buffer++;
            }

            for (int i = 0; i < indices.size(); i++) {

                m_indexBuffer->index = indices[i];
                m_indexBuffer++;
            }

            end(object);

            for (int i = 0; i < m_textureSlots.size(); i++) {

                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
            }

            flush(object);
        }

        void Renderer3D::renderSkybox(const Object::Object& object) {

            begin(object);

            const std::vector<float3>& vertices = object.getModel()->getVertices();
            const float3& position = object.getPosition();
            const float3& scale = object.getScale();
            const GLuint tid = object.getTID();

            for (int i = 0; i < vertices.size(); i++) {

                m_buffer->vertex = (vertices[i] * scale) + position;
                m_buffer++;
            }

            end(object);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, tid);

            flush(object);
        }

        void Renderer3D::renderDynamicSkybox(const Object::Object& object) {

            begin(object);

            const std::vector<float3>& vertices = object.getModel()->getVertices();
            const float3& position = object.getPosition();
            const float3& scale = object.getScale();
            
            for (int i = 0; i < vertices.size(); i++) {

                m_buffer->vertex = (vertices[i] * scale) + position;
                m_buffer++;
            }

            end(object);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, object.getTID());
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_CUBE_MAP, object.getTID2());

            flush(object);
        }

        void Renderer3D::renderTerrain(const Object::Object& object) {

            begin(object);

            const float3& position = object.getPosition();
            const std::vector<float3>& vertices = object.getModel()->getVertices();
            const float3& scale = object.getScale();
            const std::vector<float2>& UVs = object.getModel()->getUVs();
            const std::vector<float3>& normals = object.getModel()->getNormals();
            const std::vector<GLushort>& indices = object.getModel()->getIndices();
            const float& shineDamper = object.getShineDamper();
            const float& reflectivity = object.getReflectivity();
            const float4& color = object.getColor();
            const GLuint tid = object.getTID();
            const float& textureScale = object.getTextureScale();

            int r = color.x * 255.0f;
            int g = color.y * 255.0f;
            int b = color.z * 255.0f;
            int a = color.w * 255.0f;

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

                        end(object);
                        begin(object);
                    }

                    m_textureSlots.push_back(tid);
                    ts = (float)(m_textureSlots.size());
                }
            }
            else {

                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.x * 255.0f;

                c = a << 24 | b << 16 | g << 8 | r;
            }

            for (int i = 0; i < vertices.size(); i++) {

                m_buffer->vertex = (vertices[i] * scale) + position;

                if (UVs.size() > 0) {

                    m_buffer->uv = UVs[i];
                }
                m_buffer->tid = ts;
                m_buffer->normal = normals[i];
                m_buffer->color = c;
                m_buffer->shine = shineDamper;
                m_buffer->reflectivity = reflectivity;
                m_buffer->textureScale = textureScale;
                m_buffer++;
            }

            for (int i = 0; i < indices.size(); i++) {

                m_indexBuffer->index = indices[i];
                m_indexBuffer++;
            }

            end(object);

            for (int i = 0; i < m_textureSlots.size(); i++) {

                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
            }

            flush(object);
        }
    }
}