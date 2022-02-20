/*

	Mach::GL (Alpha)

*/

#include "../../Headers/Scene/Group.h"

namespace MachGL {
	namespace Scene {

		Group::Group(const Graphics::MACH_SHADER& shader, const matrix4x4& projectionMatrix) {

			m_shader = shader;
			m_matrixUBO = Graphics::UniformBuffer::createUniformBuffer(sizeof(matrix4x4) * 2, 0);
			m_matrixUBO->configureUBO(m_shader, "Matrices");
			m_matrixUBO->pushToBuffer(projectionMatrix);
			m_lightsUBO = Graphics::UniformBuffer::createUniformBuffer(sizeof(Object::LightProperties) * 12, 1);;
			m_lightsUBO->configureUBO(m_shader, "Lights");

			Object::Light light(float3(5, 10, 10), float4(0, 0, 1, 1));
			Object::Light sun(float3(0, 70, 0), float4(1, 1, 0.8f, 1));

			light.setAttenuation(float4(1, 0.002f, 0.004f, 1));
			light.setBrightness(0.6f);
			sun.setBrightness(0.7f);

			m_lights.push_back(light);
			m_lights.push_back(sun);

			m_lights.push_back(light);

			for (uint32_t i = 0; i < MAX_LIGHTS; i++) {

				if (i < m_lights.size()) 
					m_lightsUBO->pushToBuffer(m_lights[i].getProperties());
				else
					m_lightsUBO->pushToBuffer(Object::defaultLightProperties);
			}
		}

		MACH_GROUP Group::createGroup(const Graphics::MACH_SHADER& shader, const matrix4x4& projectionMatrix) {
			return make_sPoint<Group>(shader, projectionMatrix);
		}
	}
}