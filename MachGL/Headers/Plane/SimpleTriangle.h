/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Image.h"
#include "../Graphics/Shader.h"
#include "Plane.h"
#include "../Maths/Matrix.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/Framebuffer.h"

namespace MachGL {
	namespace Plane {

		class SimpleTriangle {

			private:
				float2 m_position;
				float2 m_size;
				float4 m_color = float4(1);
				sPoint<Graphics::Image> m_image = nullptr;
				matrix4x4 m_projection;
				Graphics::Shader* m_shader = nullptr;
				sPoint<Plane> m_plane = nullptr;
				std::vector<Plane> m_planes;
				float m_windowWidth;
				float m_windowHeight;
				Graphics::Renderer2D* m_renderer = nullptr;
				float m_alpha = 1.0f;

				GLint m_TIDs[32] = {
					0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
					16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
				};

			public:

				SimpleTriangle(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const float& windowWidth, const float& windowHeight);
				SimpleTriangle(const float2& position, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight);
				void render();
				~SimpleTriangle();
				inline void setAlpha(const float& alpha) { m_alpha = alpha; }
		};
	}
}
