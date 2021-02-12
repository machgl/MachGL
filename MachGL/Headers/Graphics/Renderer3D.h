#pragma once

#include "../Core/Includes.h"
#include "../Object/Object.h"
#include "Shader.h"
#include "../Maths/Vector.h"
#include "../Object/Camera.h"

namespace MachGL {
    namespace Graphics {

        class Renderer3D {

            private:
                std::vector<GLuint> m_textureSlots;
                Vertex* m_buffer = nullptr;
                Index* m_indexBuffer = nullptr;

            public:
                void submit(const std::vector<Object::Object>& objects);
                void submit(const std::vector<Object::Object>& objects, const Object::Camera& camera, const float& renderDistance);
                Renderer3D() = default;
                ~Renderer3D();
            
            private:
                void begin(const Object::Object& object);
                void end(const Object::Object& object);
                void flush(const Object::Object& object);
                void renderMesh(const Object::Object& object);
                void renderSkybox(const Object::Object& object);
                void renderDynamicSkybox(const Object::Object& object);
                void renderTerrain(const Object::Object& object);
        };
    }
}