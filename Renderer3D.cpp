#pragma once

#include "Renderer3D.h"
#include "Vector.h"

namespace MachGL {
    namespace Graphics {

        Renderer3D::~Renderer3D() {

            delete m_buffer;
            delete m_indexBuffer;
        }

        void Renderer3D::begin(const Object::Object& object) {

            glBindBuffer(GL_ARRAY_BUFFER, object.getVBO());
            m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            if (object.getType() == Object::ObjectType::MESH) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.getIBO());
                m_indexBuffer = (Index*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
            }
        }

        void Renderer3D::end(const Object::Object& object) {

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            if (object.getType() == Object::ObjectType::MESH) {

                glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }

        void Renderer3D::submit(const std::vector<Object::Object>& objects) {

            for (int i = 0; i < objects.size(); i++) {

                if (objects[i].getType() == Object::ObjectType::MESH) {

                    begin(objects[i]);

                    const float3& position = objects[i].getPosition();
                    const std::vector<float3>& vertices = objects[i].getModel()->getVertices();
                    const float3& scale = objects[i].getScale();
                    const std::vector<float2>& UVs = objects[i].getModel()->getUVs();
                    const std::vector<float3>& normals = objects[i].getModel()->getNormals();
                    const std::vector<GLushort>& indices = objects[i].getModel()->getIndices();
                    const float& shineDamper = objects[i].getShineDamper();
                    const float& reflectivity = objects[i].getReflectivity();
                    const float4& color = objects[i].getColor();
                    const GLuint tid = objects[i].getTID();
                    const float& textureScale = objects[i].getTextureScale();

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

                                end(objects[i]);
                                begin(objects[i]);
                            }

                            m_textureSlots.push_back(tid);
                            ts = (float)(m_textureSlots.size());
                        }

                    } else {

                        int r = color.x * 255.0f;
                        int g = color.y * 255.0f;
                        int b = color.z * 255.0f;
                        int a = color.x * 255.0f;

                        c = a << 24 | b << 16 | g << 8 | r;
                    }

                    for (int j = 0; j < vertices.size(); j++) {

                        m_buffer->vertex = (vertices[j] * scale) + position;

                        if (UVs.size() > 0) {

                            m_buffer->uv = UVs[j];
                        }
                        m_buffer->tid = ts;
                        m_buffer->normal = normals[j];
                        m_buffer->color = c;
                        m_buffer->shine = shineDamper;
                        m_buffer->reflectivity = reflectivity;
                        m_buffer->textureScale = textureScale;
                        m_buffer++;
                    }

                    for (int j = 0; j < indices.size(); j++) {

                        m_indexBuffer->index = indices[j];
                        m_indexBuffer++;
                    }

                    end(objects[i]);

                    for (int j = 0; j < m_textureSlots.size(); j++) {

                        glActiveTexture(GL_TEXTURE0 + j);
                        glBindTexture(GL_TEXTURE_2D, m_textureSlots[j]);
                    }

                    glBindVertexArray(objects[i].getVAO());
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i].getIBO());

                    glEnable(GL_CULL_FACE);
                    glCullFace(GL_BACK);
                    glFrontFace(GL_CCW);
                    glDrawElements(GL_TRIANGLES, objects[i].getModel()->getIndexSize(), GL_UNSIGNED_SHORT, NULL);
                    glDisable(GL_CULL_FACE);
            
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    glBindVertexArray(0);
                } 

                if (objects[i].getType() == Object::ObjectType::SKYBOX) {

                    begin(objects[i]);

                    const std::vector<float3>& vertices = objects[i].getModel()->getVertices();
                    const float3& position = objects[i].getPosition();
                    const float3& scale = objects[i].getScale();
                    const GLuint tid = objects[i].getTID();
                   
                    for (int i = 0; i < vertices.size(); i++) {

                        m_buffer->vertex = (vertices[i] * scale) + position;
                        m_buffer++;
                    }

                    end(objects[i]);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, tid);

                    glBindVertexArray(objects[i].getVAO());
                    
                    glDrawArrays(GL_TRIANGLES, 0, objects[i].getModel()->getVertices().size());
                    
                    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
                    glBindVertexArray(0);
                }
            }
        }
   }
}