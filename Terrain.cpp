/*

Mach::GL (Alpha)

*/

#include "Terrain.h"

namespace MachGL {
	namespace Object {
	
		Terrain::Terrain(int size, int vertexCount) : m_size(size), m_vertexCount(vertexCount) {

			m_model = generateTerrain();
		}

		Model* Terrain::generateTerrain() {

			const int count = m_vertexCount * m_vertexCount;
			std::vector<float3> vertices(count);
			std::vector<float3> normals(count);
			std::vector<float2> textureCoords(count);
			std::vector<GLushort> indices(6 * (m_vertexCount - 1) * (m_vertexCount - 1));
			int vertexPointer = 0;

			for (int i = 0; i < m_vertexCount; i++) {
				for (int j = 0; j < m_vertexCount; j++) {

					vertices[vertexPointer].x = (float) j / ((float) m_vertexCount - 1) * m_size;
					vertices[vertexPointer].y = 0;
					vertices[vertexPointer].z = (float) i / ((float) m_vertexCount - 1) * m_size;
					normals[vertexPointer].x = 0;
					normals[vertexPointer].y = 1;
					normals[vertexPointer].z = 0;
					textureCoords[vertexPointer].x = (float) j / ((float) m_vertexCount - 1);
					textureCoords[vertexPointer].y = (float) i / ((float) m_vertexCount - 1);
					vertexPointer++;
				}
			}

			int pointer = 0;

			for (int gz = 0; gz < m_vertexCount - 1; gz++) {
				for (int gx = 0; gx < m_vertexCount - 1; gx++) {

					int topLeft = (gz * m_vertexCount) + gx;
					int topRight = topLeft + 1;
					int bottomLeft = ((gz + 1) * m_vertexCount) + gx;
					int bottomRight = bottomLeft + 1;
					indices[pointer++] = topLeft;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = topRight;
					indices[pointer++] = topRight;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = bottomRight;
				}
			}

			return new Model(vertices, normals, textureCoords, indices);
		}
	}
}
