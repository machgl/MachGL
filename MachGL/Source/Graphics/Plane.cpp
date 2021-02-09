/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/Plane.h"

namespace MachGL {
	namespace Graphics {

		Plane::Plane(const float3& position, const float2& size, const float4& color)
			: m_position(position), m_size(size), m_color(color) { 

			m_shape = PlaneShape::QUAD;
			init();
		}

		Plane::Plane(const float3& position, const float2& size, const sPoint<Image>& image)
			: m_position(position), m_size(size), m_image(image) { 
		
			m_shape = PlaneShape::QUAD;
			m_color = float4();
			init();
		}

		Plane::Plane(const float3& position, const float2& size, const GLuint& texture) 
			: m_position(position), m_size(size), m_texture(texture) {
			
			m_shape = PlaneShape::QUAD;
			m_color = float4();
			m_type = PlaneType::DYNAMIC;
			init();
		}

		void Plane::init() {

			switch (m_shape) {

				case PlaneShape::QUAD:
					m_vertices = m_quadVertices;
					m_indices = m_quadIndices;
					m_UVs = m_quadUVs;
					break;
				default:
					break;
			}

			int vertex_index = 0;
			int UV_index = 1;
			int TID_index = 2;
			int color_index = 3;

			int vertexSize = sizeof(Vertex);
			int vertexBufferSize = m_vertices.size() * vertexSize;
			int indexBufferSize = m_indices.size() * sizeof(Index);

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glEnableVertexAttribArray(vertex_index);
			glEnableVertexAttribArray(UV_index);
			glEnableVertexAttribArray(TID_index);
			glEnableVertexAttribArray(color_index);

			glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)0);
			glVertexAttribPointer(UV_index, 2, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, uv)));
			glVertexAttribPointer(TID_index, 1, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, tid)));
			glVertexAttribPointer(color_index, 4, GL_FLOAT, GL_FALSE, vertexSize, (const GLvoid*)(offsetof(Vertex, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
		}
	}
}