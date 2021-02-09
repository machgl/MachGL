/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/SimpleRect.h"

namespace MachGL {
	namespace Graphics {


		SimpleRect::SimpleRect(const float2& pos, const float2& size, const sPoint<Image>& image, const float& windowWidth, const float& windowHeight)
			: m_pos(pos), m_size(size), m_image(image), m_windowWidth(windowWidth), m_windowHeight(windowHeight) { 

			m_projection = Maths::Matrix::simpleOrthographic(windowWidth, windowHeight);
			m_shader = new Shader("MachGL/CoreAssets/CoreShaders/simpleRect.vert", "MachGL/CoreAssets/CoreShaders/simpleRect.frag");
			m_dynamicShader = nullptr;
			m_plane = make_sPoint<Plane>(Plane(float3(m_pos.x, m_pos.y, 0), m_size, m_image));
			m_renderer = new Renderer2D();

			m_planes.push_back(*m_plane);
		}

		SimpleRect::SimpleRect(const float2& pos, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight)
			: m_pos(pos), m_size(size), m_color(color), m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

			m_projection = Maths::Matrix::simpleOrthographic(windowWidth, windowHeight);
			m_image = nullptr;
			m_shader = new Shader("MachGL/CoreAssets/CoreShaders/simpleRect.vert", "MachGL/CoreAssets/CoreShaders/simpleRect.frag");
			m_dynamicShader = nullptr;
			m_plane = make_sPoint<Plane>(Plane(float3(m_pos.x, m_pos.y, 0), m_size, m_color));
			m_renderer = new Renderer2D();

			m_planes.push_back(*m_plane);
		}

		SimpleRect::SimpleRect(const float2& pos, const float2& size, const GLuint& texture, const float& windowWidth, const float& windowHeight) 
			: m_pos(pos), m_size(size), m_texture(texture), m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

			m_projection = Maths::Matrix::simpleOrthographic(windowWidth, windowHeight);
			m_color = float4();
			m_image = nullptr;
			m_shader = nullptr;
			m_dynamicShader = new Shader("MachGL/CoreAssets/CoreShaders/dynamicRect.vert", "MachGL/CoreAssets/CoreShaders/dynamicRect.frag");
			m_plane = make_sPoint<Plane>(Plane(float3(m_pos.x, m_pos.y, 0), m_size, m_texture));
			m_renderer = new Renderer2D();

			m_planes.push_back(*m_plane);
		}

		void SimpleRect::render() {

			if (m_plane->getType() == PlaneType::STATIC) {

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

			if (m_plane->getType() == PlaneType::DYNAMIC) {

				m_dynamicShader->enable();
				m_dynamicShader->setUniformMatrix4fv("_simple_pr_matrix", m_projection);
				glActiveTexture(GL_TEXTURE0 + m_texture);
				glBindTexture(GL_TEXTURE_2D, m_texture);
				m_dynamicShader->setUniform1i("_dynamicTexture", m_texture);
				m_renderer->submit(m_planes);
				m_dynamicShader->disable();
			}
		}

		SimpleRect::~SimpleRect() {

			delete m_shader;
			delete m_renderer;
		}
	}
}