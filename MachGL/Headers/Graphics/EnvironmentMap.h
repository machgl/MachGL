/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/DataStructures.h"
#include "../Core/Includes.h"
#include "Renderer3D.h"
#include "../Object/Object.h"
#include "../Object/Camera.h"
#include "../Object/Skybox.h"

namespace MachGL {
	namespace Graphics {

		class EnvironmentMap {

			protected:
				MACH_RENDERER_3D m_renderer = nullptr;
				uint32_t		 m_fbo = 0;
				uint32_t		 m_rbo = 0;
				uint32_t		 m_textureColorBuffer = 0;
				float			 m_size = 0;
				WindowDimension  m_windowDimension;
				matrix4x4		 m_projection;
				float3			 m_position;
				MACH_SHADER	     m_shader = nullptr;

			public:
				static sPoint<EnvironmentMap> createEnvironmentMap(const float& size, const WindowDimension& windowDimension);

				EnvironmentMap() = default;
				~EnvironmentMap() = default;
				virtual void capture() = 0;
				virtual void stop() = 0;
				virtual void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera) = 0;
				virtual void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const Object::MACH_SKYBOX& skybox) = 0;
				const uint32_t& getEnvironmentMap() const { return m_textureColorBuffer; }
			protected:
				virtual void init() = 0;
		};

		using MACH_ENVIRONMENT_MAP = sPoint<EnvironmentMap>;
	}
}
