/*

Mach::Gl (Alpha)

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

		class SimpleRect {

			private:
				float2 m_position;
				float2 m_size;
				float4 m_color = float4(1);
				sPoint<Graphics::Image> m_image = nullptr;
				matrix4x4 m_projection;
				uPoint<Graphics::Shader> m_shader;
				uPoint<Plane> m_plane = nullptr;
				std::vector<Plane> m_planes;
				WindowDimension m_windowDimension;
				GLuint m_texture;
				Graphics::Renderer2D m_renderer;
				float m_alpha = 1.0f;
				float m_radius = 0;
				
			public:
				SimpleRect(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const WindowDimension& windowDimension);
				SimpleRect(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension);
				void render();
				~SimpleRect() = default;

				inline void setAlpha(const float& alpha) { m_alpha = alpha; }
				inline void setRadius(const float& radius) { m_radius = radius; }
		};
	}
}
