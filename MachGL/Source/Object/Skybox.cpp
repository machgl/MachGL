/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Skybox.h"

namespace MachGL {
	namespace Object {
		Skybox::Skybox(Graphics::Image* image)
        : m_image(image) {
		    
            m_object = new Object(new Model(makeVertices()), float3(0), m_image, ObjectType::SKYBOX);
            m_objects.push_back(*m_object);
            m_shader = new Graphics::Shader("MachGL/CoreAssets/CoreShaders/skybox.vert", "MachGL/CoreAssets/CoreShaders/skybox.frag");
		}

        std::vector<float3> Skybox::makeVertices() {

            std::vector<float3> verts;
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            verts.push_back(float3(-1.0f, -1.0f, -1.0f));
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            verts.push_back(float3(1.0f, 1.0f, -1.0f));
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            verts.push_back(float3(-1.0f, -1.0f, -1.0f));
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            verts.push_back(float3(-1.0f, 1.0f, 1.0f));
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            verts.push_back(float3(1.0f, -1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, -1.0f));
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            verts.push_back(float3(-1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, -1.0f, 1.0f));
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            verts.push_back(float3(1.0f, 1.0f, -1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(1.0f, 1.0f, 1.0f));
            verts.push_back(float3(-1.0f, 1.0f, 1.0f));
            verts.push_back(float3(-1.0f, 1.0f, -1.0f));
            
            verts.push_back(float3(-1.0f, -1.0f, -1.0f));
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            verts.push_back(float3(1.0f, -1.0f, -1.0f));
            verts.push_back(float3(-1.0f, -1.0f, 1.0f));
            verts.push_back(float3(1.0f, -1.0f, 1.0f));
            return verts;
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
