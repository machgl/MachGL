/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/EnvironmentMap.h"
#include "../../Headers/API/OpenGL/OpenGLEnvironmentMap.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Graphics {

		EnvironmentMap::EnvironmentMap(const float& size, const WindowDimension& windowDimension) {

			m_size = size;
			m_windowDimension = windowDimension;
			m_renderer = Renderer3D::createRenderer();
			m_projection = glm::perspective(90, 1, 1, 1000);
			m_shader = Shader::createShader("../MachGL/CoreAssets/CoreShaders/reflectedObject.mglsdr");
			m_UBO = UniformBuffer::createUniformBuffer(sizeof(matrix4x4), 2);
			m_UBO->configureUBO(m_shader, "Matrices");
			m_UBO->pushToBuffer(m_projection);
		}

		MACH_ENVIRONMENT_MAP EnvironmentMap::createEnvironmentMap(const float& size, const WindowDimension& windowDimension) {

			switch (GraphicsAPI::getGraphicsAPI()) {

				case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLEnvironmentMap>(size, windowDimension);
				default: return make_sPoint<OpenGLEnvironmentMap>(size, windowDimension);
			}
		}

		void EnvironmentMap::reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera) {
		
			for (uint32_t i = 0; i < 6; i++) {

				renderFace(objects, camera, i);
			}
		}
		void EnvironmentMap::reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const Object::MACH_SKYBOX& skybox) {

			Object::Camera tempCamera = camera;

			for (uint32_t i = 0; i < 6; i++) {

				renderFace(objects, camera, i);
				skybox->render(m_projection, tempCamera.getViewMatrix(i));
			}
		}
	}
}
