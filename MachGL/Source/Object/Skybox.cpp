/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Skybox.h"

namespace MachGL {
	namespace Object {

		Skybox::Skybox(const Graphics::MACH_IMAGE& image)
        : m_image(image) {
		    
            m_renderer = Graphics::Renderer3D::createRenderer();
            m_object = Object::Object::createObject(make_sPoint<Model>(makeVertices()), float3(0), m_image, nullptr, ObjectType::SKYBOX);
            m_object->create();
            m_objects.push_back(m_object);
            m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/skybox.vert", "../MachGL/CoreAssets/CoreShaders/skybox.frag");
            m_type = SkyboxType::STATIC;
		}

        Skybox::Skybox(const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2)
            : m_image(image), m_image2(image2) {

            m_renderer = Graphics::Renderer3D::createRenderer();
            m_object = Object::Object::createObject(make_sPoint<Model>(makeVertices()), float3(0), m_image, m_image2, ObjectType::SKYBOX);
            m_object->create();
            m_objects.push_back(m_object);
            m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/skybox.vert", "../MachGL/CoreAssets/CoreShaders/skybox.frag");
            m_type = SkyboxType::DYNAMIC;
        }

        Skybox::Skybox(const GLuint& cubemapID) {

            m_renderer = Graphics::Renderer3D::createRenderer();
            m_image = Graphics::Image::createImage(cubemapID);
            m_object = Object::Object::createObject(make_sPoint<Model>(makeVertices()), float3(0), m_image, nullptr, ObjectType::SKYBOX);
            m_object->create();
            m_objects.push_back(m_object);
            m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/skybox.vert", "../MachGL/CoreAssets/CoreShaders/skybox.frag");
            m_type = SkyboxType::STATIC;
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

        void Skybox::cycle() {
            
            float time = (float)m_timer.elapsedTimeSeconds();

            if (time < m_tenPercent) 
                m_blendFactor = 1- (time / m_tenPercent);
            if (time >= m_tenPercent && time < m_half) 
                m_blendFactor = 0;
            if (time >= m_half && time < m_half + m_tenPercent) 
                m_blendFactor = (time - m_half) / m_tenPercent;
            if (time >= m_half + m_tenPercent) 
                m_blendFactor = 1;
        
            if (time > m_cycleTime) 
                m_timer.reset();
        }

        void Skybox::render(const matrix4x4& projection, const matrix4x4& view) {

            cycle();

            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);

            m_shader->enable();
            m_shader->setUniformMatrix4fv("_pr_matrix", projection);
            m_shader->setUniformMatrix4fv("_vw_matrix", matrix4x4(glm::mat3(view)));

            if (m_type == SkyboxType::STATIC)
                m_shader->setUniform1i("_skybox", m_image->getTID());

            if (m_type == SkyboxType::DYNAMIC) {

                m_shader->setUniform1i("_skybox", m_image->getTID());
                m_shader->setUniform1i("_skybox2", m_image2->getTID());
                m_shader->setUniform1i("_skyboxes", (GLuint)2);
                m_shader->setUniform1f("_blendFactor", m_blendFactor);
            }

            m_renderer->submit(m_objects);
            m_shader->disable();

            glDepthFunc(GL_LESS);
            glDepthMask(GL_TRUE);
        }
	}
}
