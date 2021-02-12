/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/SimpleTriangle.h"

namespace MachGL {
	namespace Plane {

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const sPoint<Graphics::Image>& image, const float& windowWidth, const float& windowHeight)
			: m_position(position), m_size(size), m_image(image), m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowWidth, m_windowHeight);
			m_shader = new Graphics::Shader("MachGL/CoreAssets/CoreShaders/simple.vert", "MachGL/CoreAssets/CoreShaders/simple.frag");
			m_plane = make_sPoint<Plane>(Plane(float3(m_position.x, m_position.y, 0), m_size, m_image, PlaneShape::TRIANGLE));
			m_renderer = new Graphics::Renderer2D();
			m_planes.push_back(*m_plane);
		}

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight) 
			: m_position(position), m_size(size), m_color(color), m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

			m_projection = Maths::Matrix::simpleOrthographic(m_windowWidth, m_windowHeight);
			m_shader = new Graphics::Shader("MachGL/CoreAssets/CoreShaders/simple.vert", "MachGL/CoreAssets/CoreShaders/simple.frag");
			m_plane = make_sPoint<Plane>(Plane(float3(m_position.x, m_position.y, 0), m_size, m_color, PlaneShape::TRIANGLE));
			m_renderer = new Graphics::Renderer2D();
			m_planes.push_back(*m_plane);

		}

		void SimpleTriangle::render() {
		
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform1iv("_simple_TIDs", m_TIDs, 32);
			m_shader->setUniformMatrix4fv("_simple_pr_matrix", m_projection);
			m_shader->setUniform1f("_simple_alpha", m_alpha);
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
