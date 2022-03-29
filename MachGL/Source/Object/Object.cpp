/*
 
    MachGL (Alpha)
 
 */

#include "../../Headers/Object/Object.h"
#include "../../Headers/API/OpenGL/OpenGLObject.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Object {
        
        MACH_OBJECT Object::createObject() {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLObject>();
                default: return make_sPoint<OpenGLObject>();
            }
        }
    
        MACH_OBJECT Object::createObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLObject>(model, position, image);
                default: return make_sPoint<OpenGLObject>(model, position, image);
            }
        }
        
        MACH_OBJECT Object::createObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const ObjectType& type) {

            switch (GraphicsAPI::getGraphicsAPI()) {
            case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLObject>(model, position, image, type);
            default: return make_sPoint<OpenGLObject>(model, position, image, type);
            }
        }

        MACH_OBJECT Object::createObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2, const ObjectType& type) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLObject>(model, position, image, image2, type);
                default: return make_sPoint<OpenGLObject>(model, position, image, image2, type);
            }
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

            for (uint32_t i = 0; i < m_model->getVertexSize(); i++) {

                if (m_model->getVertices()[i].x < minX) minX = m_model->getVertices()[i].x;
                if (m_model->getVertices()[i].x > maxX) maxX = m_model->getVertices()[i].x;
                if (m_model->getVertices()[i].y < minY) minY = m_model->getVertices()[i].y;
                if (m_model->getVertices()[i].y > maxY) maxY = m_model->getVertices()[i].y;
                if (m_model->getVertices()[i].z < minZ) minZ = m_model->getVertices()[i].z;
                if (m_model->getVertices()[i].z > maxZ) maxZ = m_model->getVertices()[i].z;
            }

            float3 size(maxX - minX, maxY - minY, maxZ - minZ);
            float3 center((minX + maxX) / 2.0f, (minY + maxY) / 2.0f, (minZ + maxZ) / 2.0f);
            size *= m_properties.scale;
            center += m_position;

            for (uint32_t i = 0; i < 8; i++) {

                cube[i] *= size;
                cube[i] += center;
            }

            m_bounds = new Bound(size, center, cube);
        }

        void Object::create() {

            loadToBuffers();
            m_objectID = rand() % 0xffffffff;
        }

        void Object::create(const ObjectProperties& properties) { 
            
            m_properties = properties;
            loadToBuffers(); 
            m_objectID = rand() % 0xffffffff;
        }
	}
}
