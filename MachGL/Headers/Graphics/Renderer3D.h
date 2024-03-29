#pragma once

#include "MachPCH.h"
#include "../Object/Object.h"
#include "Shader.h"
#include "../Maths/Vector.h"
#include "../Object/Camera.h"
#include "Submittable3D.h"

namespace MachGL {
    namespace Graphics {

        class Renderer3D {

            public:
            
                static sPoint<Renderer3D> createRenderer();
                
                Renderer3D()  = default;
                ~Renderer3D() = default;
                
                /// <summary>
				/// Submits a list of objects for rendering and renders them.
				///	<param name="objects"></param>
				/// </summary>
                void submit(const std::vector<Object::MACH_OBJECT>& objects);

                /// <summary>
				/// Submits a list of objects for rendering and renders them but with a defined render distance, 
                /// when the objects are further away from the camera than the renderdistance the object is not sent to the renderer.
				///	<param name="objects">List of objects to send to renderer.</param>
                ///	<param name="camera">Camera object to give the position of the camera to the renderer.</param>
                ///	<param name="renderDistance">Defines the distance from the camera that the objects will render.</param>
				/// </summary>
                void submit(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const float& renderDistance);

                void submit(const Object::MACH_OBJECT& object);

                void submit(const Object::MACH_OBJECT& object, const Object::Camera& camera, const float& renderDistance);

                void submit(const std::vector<Submittable3D>& submittables);
            
            protected:
                virtual void flush(const Object::MACH_OBJECT& object) = 0;
        };
        
        using MACH_RENDERER_3D = sPoint<Renderer3D>;
    }
}
