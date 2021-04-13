/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/PostEffect.h"

namespace MachGL {
	namespace Graphics {

		PostEffect::PostEffect(const WindowDimension& windowDimension) : m_windowDimension(windowDimension) {

			m_width = m_windowDimension.width;
			m_height = m_windowDimension.height;
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);

			m_framebuffer = make_sPoint<Framebuffer>((const float)m_width, (const float)m_height);
			m_framebuffer->setColorDepth(ColorDepth::MACH_32_BIT);
			m_framebuffer->init();
			
			m_image = make_sPoint<Image>(m_framebuffer->getColorTexture());

			m_planeProperties.position = float3(0);
			m_planeProperties.size = float2(m_width, m_height);
			m_planeProperties.image = m_image->ref();

			m_plane = make_uPoint<Plane::Plane>(m_planeProperties);
			m_plane->create();
		}

		HDR::HDR(const WindowDimension& windowDimension) : PostEffect(windowDimension) {

			m_shader = make_uPoint<Shader>("MachGL/CoreAssets/CoreShaders/HDR.vert", "MachGL/CoreAssets/CoreShaders/HDR.frag");
		}
		
		void HDR::render() {
			
			m_shader->enable();
			m_shader->setUniform("_pr_matrix", m_projection);
			m_shader->setUniform("_exposure", m_exposure);
			m_shader->setUniform("_gamma", m_gamma);
			m_shader->setUniform("_texture", m_plane->getTID());
			m_renderer.submit(*m_plane);
			m_shader->disable();
		}
	}
}
