/*

Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Object/Object.h"
#include "../Graphics/Shader.h"
#include "../Graphics/UniformBuffer.h"
#include "../Object/Light.h"

#define MAX_LIGHTS 12

namespace MachGL {
	namespace Scene {

		class Group {

			private: 
				std::vector<Object::MACH_OBJECT> m_objects;
				std::vector<Object::Light> m_lights;
				Graphics::MACH_UNIFORM_BUFFER m_matrixUBO;
				Graphics::MACH_SHADER m_shader;
				Graphics::MACH_UNIFORM_BUFFER m_lightsUBO;
			
			public:
				Group(const Graphics::MACH_SHADER& shader, const matrix4x4& projectionMatrix);
				Group() = default;
				~Group() = default;
				inline void pushObject(const Object::MACH_OBJECT& object) { m_objects.push_back(object); }
				inline const std::vector<Object::MACH_OBJECT>& getObjects() { return m_objects; }
				inline const Graphics::MACH_UNIFORM_BUFFER& getMatrixUBO() { return m_matrixUBO; }
				inline const Graphics::MACH_SHADER& getShader() { return m_shader; }

				static sPoint<Group> createGroup(const Graphics::MACH_SHADER& shader, const matrix4x4& projectionMatrix);
		};

		using MACH_GROUP = sPoint<Group>;
	}
}
