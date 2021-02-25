#pragma once

#include "../Core/Includes.h"
#include "../Object/Object.h"
#include "Shader.h"
#include "../Maths/Vector.h"
#include "../Object/Camera.h"

namespace MachGL {
    namespace Graphics {

        class Renderer3D {

            public:
                void submit(const std::vector<Object::Object>& objects);
                void submit(const std::vector<Object::Object>& objects, const Object::Camera& camera, const float& renderDistance);
                Renderer3D() = default;
                ~Renderer3D() = default;
            
            private:
                void flush(const Object::Object& object);
        };
    }
}