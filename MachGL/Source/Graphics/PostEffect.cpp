/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/PostEffect.h"

namespace MachGL {
	namespace Graphics {

		PostEffect::PostEffect(const WindowDimension& windowDimension) : m_windowDimension(windowDimension) {

            m_renderer = Graphics::Renderer2D::createRenderer();
			m_width = m_windowDimension.width;
			m_height = m_windowDimension.height;
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);

			m_framebuffer = Graphics::Framebuffer::createFramebuffer((const float)m_width, (const float)m_height);
			m_framebuffer->setColorDepth(ColorDepth::MACH_32_BIT);
			m_framebuffer->init();
			
			m_image = Graphics::Image::createImage(m_framebuffer->getColorTexture());

			m_planeProperties.position = float3(0);
			m_planeProperties.size = float2(m_width, m_height);
			m_planeProperties.image = m_image;

			m_plane = Plane::Plane::createPlane(m_planeProperties);
			m_plane->create();
		}

		HDR::HDR(const WindowDimension& windowDimension) : PostEffect(windowDimension) {

			m_shader = Shader::createShader("../MachGL/CoreAssets/CoreShaders/HDR.mglsdr");
		}
		
		void HDR::render() {
			
			m_shader->enable();
			m_shader->setUniformMatrix4fv("_pr_matrix", m_projection);
			m_shader->setUniform1f("_exposure", m_exposure);
			m_shader->setUniform1f("_gamma", m_gamma);
			m_renderer->submit(m_plane);
			m_shader->disable();
		}

		GaussianBlur::GaussianBlur(const WindowDimension& windowDimension) : PostEffect(windowDimension) {

			m_framebuffer2 = Graphics::Framebuffer::createFramebuffer((const float)m_width, (const float)m_height);
			m_framebuffer2->setColorDepth(ColorDepth::MACH_32_BIT);
			m_framebuffer2->init();

			m_image2 = Graphics::Image::createImage(m_framebuffer2->getColorTexture());
			m_shader = Shader::createShader("../MachGL/CoreAssets/CoreShaders/HDR.mglsdr");
		}

		void GaussianBlur::blur() {

			m_shader->enable();
			m_shader->setUniformMatrix4fv("_pr_matrix", m_projection);
			m_shader->setUniform1i("_texture_to_blur", m_gaussianPasses % 2 == 0 ? m_image2->getTID() : m_image->getTID());
			
		}

		void GaussianBlur::render() {

		}
	}
}
