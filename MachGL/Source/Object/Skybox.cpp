/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Skybox.h"

namespace MachGL {
	namespace Object {

		Skybox::Skybox(const std::shared_ptr<Graphics::Image>& image) 
        : m_image(image), Object(&m_skyboxModel, float3(0, 0, 0), m_image, ObjectType::SKYBOX) {

			init();

            m_skyboxModel = Model(m_vertices);
            //this->setScale(float3(20, 20, 20));
            //m_objects.push_back(*this);
            m_shader = std::unique_ptr<Graphics::Shader>(new Graphics::Shader("MachGL/CoreAssets/CoreShaders/skybox.vert", "MachGL/CoreAssets/CoreShaders/skybox.frag"));
		}

		void Skybox::init() {

			m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));

            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));

            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));

            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));

            m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, 1.0f));
            m_vertices.push_back(float3(-1.0f, 1.0f, -1.0f));
            
            m_vertices.push_back(float3(-1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, -1.0f));
            m_vertices.push_back(float3(-1.0f, -1.0f, 1.0f));
            m_vertices.push_back(float3(1.0f, -1.0f, 1.0f));
		}

        void Skybox::render(const matrix4x4& projection, const matrix4x4& view) {

            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);

            m_shader->enable();

            m_shader->setUniformMatrix4fv("_pr_matrix", projection);
            m_shader->setUniformMatrix4fv("_vw_matrix", matrix4x4(glm::mat3(view)));
            m_shader->setUniform1i("_skybox", 0);

            m_renderer.submit(m_objects);

            m_shader->disable();

            glDepthFunc(GL_LESS);
            glDepthMask(GL_TRUE);
        }
	}
}
