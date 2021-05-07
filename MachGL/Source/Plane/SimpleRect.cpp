/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/SimpleRect.h"

namespace MachGL {
	namespace Plane {

		SimpleRect::SimpleRect(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_image(image), m_windowDimension(windowDimension) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = make_uPoint<Graphics::Shader>("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");
			
			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;

			m_plane = make_uPoint<Plane>(Plane(planeProperties));
			m_plane->create();
			m_planes.push_back(*m_plane);
		}

		SimpleRect::SimpleRect(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_color(color), m_windowDimension(windowDimension) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = make_uPoint<Graphics::Shader>("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.color = m_color;

			m_plane = make_uPoint<Plane>(Plane(planeProperties));
			m_plane->create();
			m_planes.push_back(*m_plane);
		}

		void SimpleRect::render() {

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform("_radius", m_radius);
			m_shader->setUniform("_simple_texture", m_plane->getTID());
			m_shader->setUniform("_simple_pr_matrix", m_projection);
			m_shader->setUniform("_simple_alpha", m_alpha);
			m_renderer.submit(m_planes);
			m_shader->disable();

			glDisable(GL_BLEND);
		}
	}
}