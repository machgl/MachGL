#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "../../Headers/Graphics/Image.h"
#include "Model.h"
#include "../../Headers/Maths/Maths.h"
#include "Bound.h"

namespace MachGL {
	namespace Object {

        enum class ObjectType { MESH, SKYBOX, TERRAIN };

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
        }

        class Object {

            private:

                sPoint<Model> m_model = nullptr;
                Bound* m_bounds = nullptr;
                float3 m_position;
                GLuint m_VAO;
                GLuint m_VBO;
                GLuint m_IBO;
                float4 m_color = float4(1, 1, 1, 1);
                float3 m_scale = float3(1, 1, 1);
                float m_TID;
                sPoint<Graphics::Image> m_image = nullptr;
                sPoint<Graphics::Image> m_image2 = nullptr;
                float m_shineDamper = 1;
                float m_reflectivity = 0;
                float m_textureScale = 1;
                bool m_hasTexture = true;
                void loadToVAO();
                ObjectType m_type;
                bool m_dynamicSkybox = false;

            public:
                Object();
                Object(const sPoint<Model>& model, const float3& position, const sPoint<Graphics::Image>& image);
                Object(const sPoint<Model>& model, const float3& position, const sPoint<Graphics::Image>& image, const sPoint<Graphics::Image>& image2, const ObjectType& type);
                ~Object() = default;

                inline void setShineDamper(const float& shineDamper) { m_shineDamper = shineDamper; }
                inline void setReflectivity(const float& reflectivity) { m_reflectivity = reflectivity; }
                inline void setColor(const float4& color) { m_color = color; }
                inline void setTexture(const Graphics::Image& image) { m_image = make_sPoint<Graphics::Image>(image); }
                inline void setScale(const float3& scale) { m_scale = scale; }
                inline void setTextureScale(const float& textureScale) { m_textureScale = textureScale; }
                inline const float& getShineDamper() const { return m_shineDamper; }
                inline const float& getReflectivity() const { return m_reflectivity; }
                inline const float& getTextureScale() const { return m_textureScale; }
                inline const float3& getPosition() const { return m_position; }
                inline const float4& getColor() const { return m_color; }
                inline const GLuint& getVAO() const { return m_VAO; }
                inline const GLuint& getVBO() const { return m_VBO; }
                inline const GLuint& getIBO() const { return m_IBO; }
                inline const GLuint getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
                inline const GLuint getTID2() const { return m_image2 == nullptr ? 0 : m_image2->getTID(); }
                inline const sPoint<Model>& getModel() const { return m_model; }
                inline const Bound* getBounds() const { return m_bounds; }
                inline const float3& getScale() const { return m_scale; }
                inline const ObjectType& getType() const { return m_type; }
                inline const bool& isDynamicSkybox() const { return m_dynamicSkybox; }
                
            private:
                void generateCubeBounds();
		};
	}
}
