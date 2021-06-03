/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/SimpleRect.h"

namespace MachGL {
	namespace Plane {

		SimpleRect::SimpleRect(const float2& position, const float2& size, const Graphics::MACH_IMAGE& image, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_image(image), m_windowDimension(windowDimension) {

            m_renderer = Graphics::Renderer2D::createRenderer();
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");
			
			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;

			m_plane = Plane::Plane::createPlane(planeProperties);
			m_plane->create();
			m_planes.push_back(m_plane);
		}

		SimpleRect::SimpleRect(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_color(color), m_windowDimension(windowDimension) {

            m_renderer = Graphics::Renderer2D::createRenderer();
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.color = m_color;

			m_plane = Plane::Plane::createPlane(planeProperties);
			m_plane->create();
			m_planes.push_back(m_plane);
		}

		void SimpleRect::render() {

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform1f("_radius", m_radius);
			m_shader->setUniform1i("_simple_texture", m_plane->getTID());
			m_shader->setUniformMatrix4fv("_simple_pr_matrix", m_projection);
			m_shader->setUniform1f("_simple_alpha", m_alpha);
			m_renderer->submit(m_planes);
			m_shader->disable();

			glDisable(GL_BLEND);
		}
	}
}
