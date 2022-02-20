/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Image.h"
#include "../Graphics/Shader.h"
#include "Plane.h"
#include "../Maths/Matrix.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/Framebuffer.h"
#include "../Graphics/UniformBuffer.h"

namespace MachGL {
	namespace Plane {

		class SimpleTriangle {

			private:
				float2                      m_position;
				float2                      m_size;
				float4                      m_color    = float4(1);
				Graphics::MACH_IMAGE        m_image    = nullptr;
				matrix4x4                   m_projection;
				Graphics::MACH_SHADER       m_shader   = nullptr;
				MACH_PLANE                  m_plane	   = nullptr;
				std::vector<MACH_PLANE>     m_planes;
				WindowDimension             m_windowDimension;
				Graphics::MACH_RENDERER_2D  m_renderer;
				float					    m_alpha    = 1.0f;
				Graphics::MACH_UNIFORM_BUFFER m_UBO;

			public:

				SimpleTriangle(const float2& position, const float2& size, const Graphics::MACH_IMAGE& image, const WindowDimension& windowDimension);
				SimpleTriangle(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension);
				void render();
				~SimpleTriangle() = default;
				inline void setAlpha(const float& alpha) { m_alpha = alpha; }
		};

		using MACH_SIMPLE_TRIANGLE = sPoint<SimpleTriangle>;
	}
}
