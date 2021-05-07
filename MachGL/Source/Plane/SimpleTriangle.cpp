/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/SimpleTriangle.h"

namespace MachGL {
	namespace Plane {

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_image(image), m_windowDimension(windowDimension) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = new Graphics::Shader("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;
			planeProperties.shape = PlaneShape::TRIANGLE;

			m_plane = make_sPoint<Plane>(Plane(planeProperties));
			m_renderer = new Graphics::Renderer2D();
			m_planes.push_back(*m_plane);
		}

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_color(color), m_windowDimension(windowDimension) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = new Graphics::Shader("../MachGL/CoreAssets/CoreShaders/simple.vert", "../MachGL/CoreAssets/CoreShaders/simple.frag");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;
			planeProperties.shape = PlaneShape::TRIANGLE;

			m_plane = make_sPoint<Plane>(Plane(planeProperties));
			m_renderer = new Graphics::Renderer2D();
			m_planes.push_back(*m_plane);

		}

		void SimpleTriangle::render() {
		
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform("_simple_texture", m_plane->getTID());
			m_shader->setUniform("_simple_pr_matrix", m_projection);
			m_shader->setUniform("_simple_alpha", m_alpha);
			m_renderer->submit(m_planes);
			m_shader->disable();

			glDisable(GL_BLEND);
		}

		SimpleTriangle::~SimpleTriangle() {

			delete m_shader;
			delete m_renderer;
		}
	}
}
