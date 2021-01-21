/*

Mach::GL (Alpha)

*/

#include "Terrain.h"
#include "Vector.h"

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

					float height = generateHeight(j, i);

					vertices[vertexPointer].x = (float) j / ((float) m_vertexCount - 1) * m_size;
					vertices[vertexPointer].y = height;
					vertices[vertexPointer].z = (float) i / ((float) m_vertexCount - 1) * m_size;

					float3 normal = calculateNormal(j, i);
					normals[vertexPointer].x = normal.x;
					normals[vertexPointer].y = normal.y;
					normals[vertexPointer].z = normal.z;

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

		float Terrain::generateHeight(const float& x, const float& z) {
			return 1;
		}

		float3 Terrain::calculateNormal(const float& x, const float& z) {

			float heightL = generateHeight(x - 1, z);
			float heightR = generateHeight(x + 1, z);
			float heightD = generateHeight(x, z - 1);
			float heightU = generateHeight(x, z + 1);
			float3 normal(heightL - heightR, 2, heightD - heightU);
			normal = Maths::Vector::normalize(normal);
			return normal;
		}
	}
}
