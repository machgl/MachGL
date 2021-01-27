/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "Image.h"

namespace MachGL {
	namespace Graphics {

		class Plane{

			private:
				float3 m_position;
				float2 m_size;
				float m_TID;
				float4 m_color;
				std::shared_ptr<Image> m_image;
				std::vector<float2> m_uvs;
				
				void setupUVs();
				
			public:
				Plane(const float3& position, const float2& size, const float4& color);
				Plane(const float3& position, const float2& size, const std::shared_ptr<Image>& image);

				inline const float3& getPosition() const { return m_position; }
				inline const float2& getSize() const { return m_size; }
				inline const GLuint getTID() const { return m_image == nullptr ? 0 : m_image->getTID(); }
				inline const float4& getColor() const { return m_color; }
				inline const std::vector<float2>& const getUVs() { return m_uvs; }
		};
	}
}