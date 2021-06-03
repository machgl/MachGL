/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Terrain.h"

namespace MachGL {
	namespace Object {
	
		Terrain::Terrain(const uint32_t& size, const uint32_t& vertexCount)
            : m_size(size), m_vertexCount(vertexCount) {

			m_model = generateTerrain();
		}

		Terrain::Terrain(const uint32_t& size, const uint32_t& vertexCount, const float& amplitude,
					const uint32_t& octaves, const float& roughness, const long& seed)
					: m_size(size), m_vertexCount(vertexCount), m_amplitude(amplitude), m_octaves(octaves), m_roughness(roughness), m_seed(seed) {

			m_noise = Noise(seed);
			m_model = generateTerrain();
		}

		MACH_MODEL Terrain::generateTerrain() {

			const uint32_t count = m_vertexCount * m_vertexCount;
			std::vector<float3> vertices(count);
			std::vector<float3> normals(count);
			std::vector<float2> textureCoords(count);
			std::vector<unsigned int> indices(6 * (uint64_t)(m_vertexCount - 1) * (uint64_t)(m_vertexCount - 1));
			int vertexPointer = 0;

			for (uint32_t i = 0; i < m_vertexCount; i++) {
				for (uint32_t j = 0; j < m_vertexCount; j++) {

					float height = generateHeight((float)j, (float)i);

					vertices[vertexPointer].x = (float) j / ((float) m_vertexCount - 1) * m_size;
					vertices[vertexPointer].y = height;
					vertices[vertexPointer].z = (float) i / ((float) m_vertexCount - 1) * m_size;

					float3 normal = calculateNormal((float)j, (float)i);
					normals[vertexPointer].x = normal.x;
					normals[vertexPointer].y = normal.y;
					normals[vertexPointer].z = normal.z;

					textureCoords[vertexPointer].x = (float) j / ((float) m_vertexCount - 1);
					textureCoords[vertexPointer].y = (float) i / ((float) m_vertexCount - 1);
					vertexPointer++;
				}
			}

			uint32_t pointer = 0;

			for (uint32_t gz = 0; gz < m_vertexCount - 1; gz++) {
				for (uint32_t gx = 0; gx < m_vertexCount - 1; gx++) {

					uint32_t topLeft = (gz * m_vertexCount) + gx;
					uint32_t topRight = topLeft + 1;
					uint32_t bottomLeft = ((gz + 1) * m_vertexCount) + gx;
					uint32_t bottomRight = bottomLeft + 1;
					indices[pointer++] = topLeft;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = topRight;
					indices[pointer++] = topRight;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = bottomRight;
				}
			}

			return make_sPoint<Model>(Model(vertices, normals, textureCoords, indices));
		}

		float Terrain::generateHeight(const float& x, const float& z) {
			
			if (m_octaves != 0) {

				float total = 0;
				float d = (float) pow(2, m_octaves - 1);

				for (uint32_t i = 0; i < m_octaves; i++) {

					float frequency = (float) (pow(2, i) / d);
					float amplitude = (float) pow(m_roughness, i) * m_amplitude;
					total += m_noise.noise(x * frequency, z * frequency) * amplitude;
				}

				return total;
			
			}
			else 
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
