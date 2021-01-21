/*

Mach::GL (Alpha) 


*/

#pragma once

#include "Includes.h"
#include "DataStructures.h"
#include "Image.h"

namespace MachGL {
	namespace Graphics {

		class Plane {

			private:
				float3 m_position;
				float2 m_size;
				float m_TID;
				float4 m_color;
				Image* m_image = nullptr;
				std::vector<float2> m_uvs;
				
				void setupUVs();
				
			public:
				Plane(const float3& position, const float2& size, const float4& color);
				Plane(const float3& position, const float2& size, Image* image);

				inline const float3& getPosition() const { return m_position; }
				inline const float2& getSize() const { return m_size; }
				inline const GLuint getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
				inline const float4& getColor() const { return m_color; }
				inline const std::vector<float2>& const getUVs() { return m_uvs; }
		};
	}
}