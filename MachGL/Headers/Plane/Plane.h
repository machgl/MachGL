/*

Mach::GL (Alpha) 


*/

#pragma once

#include "..//Core/Includes.h"
#include "..//Core/DataStructures.h"
#include "../Graphics/Image.h"

namespace MachGL {
	namespace Plane {

		enum class PlaneType {

			STATIC, DYNAMIC
		};

		enum class PlaneShape {

			QUAD, TRIANGLE, CUSTOM
		};

		struct PlaneProperties {

			float3					position = float3(0);
			float2					size	 = float2(1);
			float4					color	 = float4(0);
			PlaneShape				shape	 = PlaneShape::QUAD;
			Graphics::MACH_IMAGE    image	 = nullptr;
			PlaneType				type	 = PlaneType::STATIC;
		};

		class Plane{

			protected:
				float3					    m_position;
				float2					    m_size;
				float					    m_TID;
				float4					    m_color;
				Graphics::MACH_IMAGE        m_image		   = nullptr;
				uint32_t				    m_texture;
				PlaneShape				    m_shape		   = PlaneShape::QUAD;
				PlaneType				    m_type		   = PlaneType::STATIC;
				std::vector<float3>		    m_vertices;
				std::vector<unsigned short>	m_indices;
				std::vector<float2>		    m_UVs;
                uint32_t			        m_VAO;
                uint32_t				    m_VBO;
                uint32_t				    m_IBO;
				Vertex*					    m_vertexBuffer = nullptr;
				Index*					    m_indexBuffer  = nullptr;

				std::vector<float3> m_triVertices = {

					float3(0, 1, 0),
					float3(1, 1, 0),
					float3(0.5f, 0, 0)
				};

				std::vector<unsigned short> m_triIndices = {

					0, 1, 2
				};

				std::vector<float2> m_triUVs = {

					float2(0, 0),
					float2(1, 0),
					float2(0.5f, 1)
				};

				std::vector<float3> m_quadVertices = {

					float3(0, 0, 0),
					float3(0, 1, 0),
					float3(1, 1, 0),
					float3(1, 0, 0)
				};

				std::vector<unsigned short> m_quadIndices = {

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
                ~Plane() = default;
                
                static sPoint<Plane> createPlane(const PlaneProperties& properties);
                static sPoint<Plane> createPlane(const std::vector<float3>& vertices, const std::vector<unsigned short>& indices, const std::vector<float2>& uvs, const PlaneProperties& properties);
                static sPoint<Plane> createPlane(const float3& position, const float2& size, const GLuint& texture);
            
				void create();
				virtual void destroy() = 0;

				inline const float3& getPosition() const { return m_position; }
				inline const float2& getSize() const { return m_size; }
				inline const uint32_t getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
				inline const uint32_t& getTexture() const { return m_texture; }
				inline const float4& getColor() const { return m_color; }
				inline const PlaneType& getType() const { return m_type; }
				inline const PlaneShape& getShape() const { return m_shape; }
				inline const uint32_t& getVAO() const { return m_VAO; }
				inline const uint32_t& getVBO() const { return m_VBO; }
				inline const uint32_t& getIBO() const { return m_IBO; }
				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const auto& getIndices() const { return m_indices; }
				inline const std::vector<float2>& getUVs() const { return m_UVs; }

			protected:
				virtual void loadToVAO() = 0;
				virtual void loadToBuffers() = 0;
		};
    
        using MACH_PLANE = sPoint<Plane>;
	}
}
