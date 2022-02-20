/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "Model.h"

namespace MachGL {
	namespace Object {

		enum class BoundType {

			CUBE
		};

		class Bound {

			private:
				float3              m_size;
				float3              m_center;
				std::vector<float3> m_vertices;
				BoundType           m_type = BoundType::CUBE;

			public:
				Bound(const float3& size, const float3& center, const std::vector<float3>& vertices) : m_size(size), m_center(center), m_vertices(vertices) {}
				~Bound() = default;
				
				inline const float3& getSize() const { return m_size; }
				inline const float3& getCenter() const { return m_center; }	
				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const BoundType& getType() const { return m_type; }
			};

	}
}
