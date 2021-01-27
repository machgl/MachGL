/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/SimpleRect.h"

namespace MachGL {
	namespace Graphics {

		SimpleRect::SimpleRect(const float2& pos, const float2& size, const std::shared_ptr<Image>& image, const float& windowWidth, const float& windowHeight)
			: m_pos(pos), m_size(size), m_image(image), m_windowWidth(windowWidth), m_windowHeight(windowHeight),
			Plane(float3(m_pos.x, m_pos.y, 0), m_size, m_image) { 

			m_projection = Maths::Matrix::simpleOrthographic(windowWidth, windowHeight);
			m_shader = std::unique_ptr<Shader>(new Shader("MachGL/CoreAssets/CoreShaders/simpleRect.vert", "MachGL/CoreAssets/CoreShaders/simpleRect.frag"));
			m_renderer = std::unique_ptr<Renderer2D>(new Renderer2D());
		}

		SimpleRect::SimpleRect(const float2& pos, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight)
			: m_pos(pos), m_size(size), m_color(color), m_windowWidth(windowWidth), m_windowHeight(windowHeight),
			Plane(float3(m_pos.x, m_pos.y, 0), m_size, m_color) {

			m_projection = Maths::Matrix::simpleOrthographic(windowWidth, windowHeight);
			m_shader = std::unique_ptr<Shader>(new Shader("MachGL/CoreAssets/CoreShaders/simpleRect.vert", "MachGL/CoreAssets/CoreShaders/simpleRect.frag"));
			m_renderer = std::unique_ptr<Renderer2D>(new Renderer2D());
		}

		void SimpleRect::render() {

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform1iv("_simple_TIDs", m_TIDs, 32);
			m_shader->setUniformMatrix4fv("_simple_pr_matrix", m_projection);
			m_shader->setUniform1f("_simple_alpha", m_alpha);
			m_renderer->begin();
			m_renderer->submit(std::make_unique<Plane>(*this));
			m_renderer->end();
			m_renderer->flush();
			m_shader->disable();

			glDisable(GL_BLEND);
		}
	}
}