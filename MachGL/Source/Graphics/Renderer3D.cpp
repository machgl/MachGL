/*
 
    MachGL (Alpha)
 
 */

#include "../../Headers/Graphics/Renderer3D.h"
#include "../../Headers/API/OpenGL/OpenGLRenderer3D.h"
#include "../../Headers/API/API.h"

namespace MachGL {
    namespace Graphics {

        MACH_RENDERER_3D Renderer3D::createRenderer() {
        
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLRenderer3D>();
                default: return make_sPoint<OpenGLRenderer3D>();
            }
        }

        void Renderer3D::submit(const std::vector<Object::MACH_OBJECT>& objects) {
            
            for (uint32_t i = 0; i < objects.size(); i++) flush(objects[i]); 
        }

        void Renderer3D::submit(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const float& renderDistance) {

            for (uint32_t i = 0; i < objects.size(); i++) {
                
                if (objects[i]->getType() != Object::ObjectType::TERRAIN) {
                    if (Maths::Vector::distance(camera.getPosition(), objects[i]->getPosition()) <= renderDistance) flush(objects[i]);
                }
                else flush(objects[i]);
            }
        }

        void Renderer3D::submit(const Object::MACH_OBJECT& object) { flush(object); }

        void Renderer3D::submit(const Object::MACH_OBJECT& object, const Object::Camera& camera, const float& renderDistance) {

            if (object->getType() != Object::ObjectType::TERRAIN) {
                if (Maths::Vector::distance(camera.getPosition(), object->getPosition()) <= renderDistance) flush(object);
            }
            else flush(object);
        }
    }
}
