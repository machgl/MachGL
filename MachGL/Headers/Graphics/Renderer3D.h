#pragma once

#include "../../Headers/Core/Includes.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/Buffer.h"
#include "../../Headers/Object/Object.h"
#include "Shader.h"
#include "../../Headers/Maths/Vector.h"

namespace MachGL {
    namespace Graphics {

        class Renderer3D {

            private:
                std::vector<GLuint> m_textureSlots;
                Vertex* m_buffer = nullptr;
                Index* m_indexBuffer = nullptr;

            public:
                void submit(const std::vector<Object::Object>& objects);
                Renderer3D() = default;
                ~Renderer3D();
            
            private:
                void begin(const Object::Object& object);
                void end(const Object::Object& object);
                void renderMesh(const Object::Object& object);
                void renderSkybox(const Object::Object& object);
                void renderTerrain(const Object::Object& object);
        };
    }
}