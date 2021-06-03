#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Image.h"
#include "Model.h"
#include "../Maths/Maths.h"
#include "Bound.h"

namespace MachGL {
	namespace Object {

        enum class ObjectType { MESH, SKYBOX, TERRAIN };

        struct ObjectProperties {

            float  shineDamper  = 1.0f;
            float  reflectivity = 0.0f;
            float  textureScale = 1.0f;
            float3 scale        = float3(1);
            float4 color        = float4(1);
        };

        static bool isInBounds(const Bound* bound1, const Bound* bound2) {

            if (bound1->getType() == BoundType::CUBE && bound2->getType() == BoundType::CUBE) {

                float minX1 = bound1->getCenter().x - (bound1->getSize().x / 2.0f);
                float minX2 = bound2->getCenter().x - (bound2->getSize().x / 2.0f);
                float minY2 = bound2->getCenter().y - (bound2->getSize().y / 2.0f);
                float minY1 = bound1->getCenter().y - (bound1->getSize().y / 2.0f);
                float minZ1 = bound1->getCenter().z - (bound1->getSize().z / 2.0f);
                float minZ2 = bound2->getCenter().z - (bound2->getSize().z / 2.0f);

                float maxX1 = bound1->getCenter().x + (bound1->getSize().x / 2.0f);
                float maxX2 = bound2->getCenter().x + (bound2->getSize().x / 2.0f);
                float maxY2 = bound2->getCenter().y + (bound2->getSize().y / 2.0f);
                float maxY1 = bound1->getCenter().y + (bound1->getSize().y / 2.0f);
                float maxZ1 = bound1->getCenter().z + (bound1->getSize().z / 2.0f);
                float maxZ2 = bound2->getCenter().z + (bound2->getSize().z / 2.0f);

                //TODO: Bound detection

                return false;
            }
            return false;
        }

        class Object {

            protected:
                MACH_MODEL              m_model         = nullptr;
                Bound*                  m_bounds        = nullptr;
                float3                  m_position;
                uint32_t                m_VAO;
                uint32_t                m_VBO;
                uint32_t                m_IBO;
                float                   m_TID;
                Graphics::MACH_IMAGE    m_image         = nullptr;
                Graphics::MACH_IMAGE    m_image2        = nullptr;
                bool                    m_hasTexture    = true;
                ObjectType              m_type;
                bool                    m_dynamicSkybox = false;
                Vertex*                 m_vertexBuffer  = nullptr;
                Index*                  m_indexBuffer   = nullptr;
                uint32_t                m_enviromap     = 0;
                uint32_t                m_objectID;
                ObjectProperties        m_properties;
                
            public:
                
                static sPoint<Object> createObject();
                static sPoint<Object> createObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image);
                static sPoint<Object> createObject(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2, const ObjectType& type);
            
                Object() = default;
                Object(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image);
                Object(const MACH_MODEL& model, const float3& position, const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2, const ObjectType& type);
                ~Object() = default;
                void create();
                void create(const ObjectProperties& properties);
                virtual void destroy() = 0;

                inline void setTexture(const Graphics::MACH_IMAGE& image) { m_image = image; }
                inline const float& getShineDamper() const { return m_properties.shineDamper; }
                inline const float& getReflectivity() const { return m_properties.reflectivity; }
                inline const float& getTextureScale() const { return m_properties.textureScale; }
                inline const float3& getPosition() const { return m_position; }
                inline const float4& getColor() const { return m_properties.color; }
                inline const uint32_t& getVAO() const { return m_VAO; }
                inline const uint32_t& getVBO() const { return m_VBO; }
                inline const uint32_t& getIBO() const { return m_IBO; }
                inline const uint32_t getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
                inline const uint32_t getTID2() const { return m_image2 == nullptr ? 0 : m_image2->getTID(); }
                inline const auto& getModel() const { return m_model; }
                inline const Bound* getBounds() const { return m_bounds; }
                inline const float3& getScale() const { return m_properties.scale; }
                inline const ObjectType& getType() const { return m_type; }
                inline const bool& isDynamicSkybox() const { return m_dynamicSkybox; }
                inline void setEnviromentMap(const GLuint& environmentMap) { m_enviromap = environmentMap; }
                inline const uint32_t& getEnvironmentMap() const { return m_enviromap; }
                inline const uint32_t& getObjectID() const { return m_objectID; }
                
            protected:
                virtual void loadToBuffers() = 0;
                virtual void loadToVAO() = 0;
                void generateCubeBounds();
		};
    
        using MACH_OBJECT = sPoint<Object>;    
	}
}
