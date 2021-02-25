/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Particle {

		class Particle {

			public:
				float m_lifetime = 3;
				float m_time = 0;

			protected:
				std::vector<float3> m_vertices;
				std::vector<GLushort> m_indices;
				std::vector<float3> m_normals;

			public:
				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const std::vector<GLushort>& getIndices() const { return m_indices; }
				inline const std::vector<float3>& getNormals() const { return m_normals; }
				inline const float& getLifetime() const { return m_lifetime; }
				inline void setLifetime(const float& lifetime) { m_lifetime = lifetime; }
				inline float& getTime() { return m_time; }
		};
	}
}
