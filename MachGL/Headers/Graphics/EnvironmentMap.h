/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "Renderer3D.h"
#include "../Object/Object.h"
#include "../Object/Camera.h"
#include "../Object/Skybox.h"

namespace MachGL {
	namespace Graphics {

		class EnvironmentMap {

			protected:
				MACH_RENDERER_3D	m_renderer = nullptr;
				uint32_t			m_fbo = 0;
				uint32_t			m_rbo = 0;
				uint32_t			m_textureColorBuffer = 0;
				float				m_size = 0;
				WindowDimension		m_windowDimension;
				matrix4x4			m_projection = matrix4x4(0);
				float3				m_position = float3(0);
				MACH_SHADER			m_shader = nullptr;
				MACH_UNIFORM_BUFFER m_UBO = nullptr;

			public:
				static sPoint<EnvironmentMap> createEnvironmentMap(const float& size, const WindowDimension& windowDimension);

				EnvironmentMap() = default;
				~EnvironmentMap() = default;
				virtual void capture() = 0;
				EnvironmentMap(const float& size, const WindowDimension& windowDimension);
				virtual void stop() = 0;
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera);
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const Object::MACH_SKYBOX& skybox);
				const uint32_t& getEnvironmentMap() const { return m_textureColorBuffer; }
			protected:
				virtual void init() = 0;
				virtual void renderFace(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const uint32_t& face) = 0;
		};

		using MACH_ENVIRONMENT_MAP = sPoint<EnvironmentMap>;
	}
}
