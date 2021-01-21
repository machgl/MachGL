/*

Mach::GL (Alpha)

*/

#include "Plane.h"

namespace MachGL {
	namespace Graphics {

		Plane::Plane(const float3& position, const float2& size, const float4& color)
			: m_position(position), m_size(size), m_color(color) { 
		
			setupUVs();
		}

		Plane::Plane(const float3& position, const float2& size, Image* image)
			: m_position(position), m_size(size), m_image(image) { 
		
			m_color = float4();
			setupUVs();
		}

		void Plane::setupUVs() {

			m_uvs.push_back(float2(0, 1));
			m_uvs.push_back(float2(0, 0));
			m_uvs.push_back(float2(1, 0));
			m_uvs.push_back(float2(1, 1));
		}
	}
}