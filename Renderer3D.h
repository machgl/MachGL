#pragma once

#include "Includes.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Object.h"
#include "Shader.h"

namespace MachGL {
    namespace Graphics {

        class Renderer3D {

        private:
            std::vector<GLuint> m_textureSlots;
            Vertex* m_buffer = nullptr;
            Index* m_indexBuffer = nullptr;

        public:
            void submit(const std::vector<Object::Object>& objects);
            ~Renderer3D();
            
        private:
            void begin(const Object::Object& object);
            void end(const Object::Object& object);
        };
    }
}