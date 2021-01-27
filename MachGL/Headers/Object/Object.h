#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "../../Headers/Graphics/Image.h"
#include "Model.h"
#include "../../Headers/Maths/Maths.h"

namespace MachGL {
	namespace Object {

        enum class ObjectType { MESH, SKYBOX, TERRAIN };

        class Object {

            private:

                std::shared_ptr<Model> m_model;
                float3 m_position;
                GLuint m_VAO;
                GLuint m_VBO;
                GLuint m_IBO;
                float4 m_color = float4(1, 1, 1, 1);
                float3 m_scale = float3(1, 1, 1);
                float m_TID;
                std::shared_ptr<Graphics::Image> m_image;
                float m_shineDamper = 1;
                float m_reflectivity = 0;
                float m_textureScale = 1;
                bool m_hasTexture = true;
                void loadToVAO();
                ObjectType m_type;

            public:
                Object();
                Object(const std::shared_ptr<Model>& model, const float3& position, const std::shared_ptr<Graphics::Image>& image);
                Object(const std::shared_ptr<Model>& model, const float3& position, const std::shared_ptr<Graphics::Image>&, const ObjectType& type);
                ~Object();

                inline void setShineDamper(const float& shineDamper) { m_shineDamper = shineDamper; }
                inline void setReflectivity(const float& reflectivity) { m_reflectivity = reflectivity; }
                inline void setColor(const float4& color) { m_color = color; }
                inline void setTexture(const std::shared_ptr<Graphics::Image>& image) { m_image = image; }
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

                inline const std::shared_ptr<Model> getModel() const { return m_model; }
                inline const float3& getScale() const { return m_scale; }

                inline const ObjectType& getType() const { return m_type; }

		};
	}
}
