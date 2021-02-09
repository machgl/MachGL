/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "Image.h"

namespace MachGL {
	namespace Graphics {

		enum class PlaneType {

			STATIC, DYNAMIC
		};

		enum class PlaneShape {

			QUAD
		};

		class Plane{

			private:
				float3 m_position;
				float2 m_size;
				float m_TID;
				float4 m_color;
				sPoint<Image> m_image = nullptr;
				GLuint m_texture;
				PlaneType m_type = PlaneType::STATIC;
				PlaneShape m_shape = PlaneShape::QUAD;
				std::vector<float3> m_vertices;
				std::vector<GLushort> m_indices;
				std::vector<float2> m_UVs;
				GLuint m_VAO;
				GLuint m_VBO;
				GLuint m_IBO;

				std::vector<float3> m_quadVertices = {

					float3(0, 0, 0),
					float3(0, 1, 0),
					float3(1, 1, 0),
					float3(1, 0, 0)
				};

				std::vector<GLushort> m_quadIndices = {

					0, 1, 2, 2, 3, 0
				};

				std::vector<float2> m_quadUVs = {

					float2(0, 1),
					float2(0, 0),
					float2(1, 0),
					float2(1, 1)
				};

			public:
				Plane() = default;
				Plane(const float3& position, const float2& size, const float4& color);
				Plane(const float3& position, const float2& size, const sPoint<Image>& image);
				Plane(const float3& position, const float2& size, const GLuint& texture);
				~Plane() = default;

				inline const float3& getPosition() const { return m_position; }
				inline const float2& getSize() const { return m_size; }
				inline const GLuint getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
				inline const GLuint& getTexture() const { return m_texture; }
				inline const float4& getColor() const { return m_color; }
				inline const PlaneType& getType() const { return m_type; }
				inline const PlaneShape& getShape() const { return m_shape; }
				inline sPoint<Plane> ref() { return make_sPoint<Plane>(*this); }
				inline const GLuint& getVAO() const { return m_VAO; }
				inline const GLuint& getVBO() const { return m_VBO; }
				inline const GLuint& getIBO() const { return m_IBO; }
				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const std::vector<GLushort>& getIndices() const { return m_indices; }
				inline const std::vector<float2>& getUVs() const { return m_UVs; }

			private:
				void init();
		};
	}
}