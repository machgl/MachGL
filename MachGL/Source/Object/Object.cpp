#include "../../Headers/Object/Object.h"

namespace MachGL {
	namespace Object {

        Object::Object() { 
            
            m_position = float3();
            m_type = ObjectType::MESH;
            m_VAO = 0;
            m_IBO = 0;
            m_VBO = 0;
            m_TID = 0;
            m_model = NULL;
        }   

        Object::Object(Model* model, const float3& position, Graphics::Image* image)
            : m_model(model), m_position(position), m_image(image), m_type(ObjectType::MESH) {

            loadToVAO();
            generateCubeBounds();
        }

        Object::Object(Model* model, const float3& position, Graphics::Image* image, const ObjectType& type)
            : m_model(model), m_position(position), m_image(image), m_type(type) {

            loadToVAO();
            generateCubeBounds();
        }

        void Object::generateCubeBounds() {

            std::vector<float3> cube = {

                float3(-0.5f, -0.5f, -0.5f),
                float3(0.5f, -0.5f, -0.5f),
                float3(0.5f, 0.5f, -0.5f),
                float3(-0.5f, 0.5f, -0.5f),
                float3(-0.5f, -0.5f, 0.5f),
                float3(0.5f, -0.5f, 0.5f),
                float3(0.5f, 0.5f, 0.5f),
                float3(-0.5f, 0.5f, 0.5f)
            };

            float minX, maxX, minY, maxY, minZ, maxZ;

            minX = maxX = m_model->getVertices()[0].x;
            minY = maxY = m_model->getVertices()[0].y;
            minZ = maxZ = m_model->getVertices()[0].z;

            for (int i = 0; i < m_model->getVertexSize(); i++) {

                if (m_model->getVertices()[i].x < minX) minX = m_model->getVertices()[i].x;
                if (m_model->getVertices()[i].x > maxX) maxX = m_model->getVertices()[i].x;
                if (m_model->getVertices()[i].y < minY) minY = m_model->getVertices()[i].y;
                if (m_model->getVertices()[i].y > maxY) maxY = m_model->getVertices()[i].y;
                if (m_model->getVertices()[i].z < minZ) minZ = m_model->getVertices()[i].z;
                if (m_model->getVertices()[i].z > maxZ) maxZ = m_model->getVertices()[i].z;
            }

            float3 size(maxX - minX, maxY - minY, maxZ - minZ);
            float3 center((minX + maxX) / 2.0f, (minY + maxY) / 2.0f, (minZ + maxZ) / 2.0f);
            size *= m_scale;
            center += m_position;

            for (int i = 0; i < 8; i++) {

                cube[i] *= size;
                cube[i] += center;
            }

            m_bounds = new Bound(size, center, cube);
        }

        void Object::loadToVAO() {

            int vertex_index = 0;
            int uv_index = 1;
            int tid_index = 2;
            int normal_index = 3;
            int color_index = 4;
            int shine_index = 5;
            int reflectivity_index = 6;
            int texture_scale_index = 7;

            int vertexSize = sizeof(Vertex);
            int vertexBufferSize = m_model->getVertexSize() * vertexSize;
            int indexBufferSize = m_model->getIndexSize() * sizeof(Index);

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

        Object::~Object() {   }
	}
}