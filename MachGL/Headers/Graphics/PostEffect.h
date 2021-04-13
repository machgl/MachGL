/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Framebuffer.h"
#include "../Graphics/Image.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Renderer2D.h"
#include "../Maths/Matrix.h"

namespace MachGL {
	namespace Graphics {
	
		class PostEffect {

			protected:
				WindowDimension m_windowDimension;
				sPoint<Framebuffer> m_framebuffer;
				sPoint<Image> m_image;
				uPoint<Shader> m_shader;
				uPoint<Plane::Plane> m_plane;
				Renderer2D m_renderer;
				uint32_t m_width = 0, m_height = 0;
				matrix4x4 m_projection;
				Plane::PlaneProperties m_planeProperties;

			public:
				PostEffect(const WindowDimension& windowDimension);
				~PostEffect() = default;
				inline virtual void capture() { m_framebuffer->capture(); }
				inline virtual void stop() { m_framebuffer->stop(); }
				virtual void render() = 0;
		};

		class HDR : public PostEffect {

			private:
				float m_exposure = 1.0f;
				float m_gamma = 2.2f;
				bool m_bloom = false;
				uint32_t m_gaussianPasses = 5;

			public:
				HDR(const WindowDimension& windowDimension);
				virtual void render() override;
				inline void setExposure(const float& exposure) { m_exposure = exposure; }
				inline void setGamma(const float& gamma) { m_gamma = gamma; }
				inline void bloom() { m_bloom = true; }
				inline void setGausianPasses(const uint32_t& passes) { m_gaussianPasses = passes; }
		};
	}
}
