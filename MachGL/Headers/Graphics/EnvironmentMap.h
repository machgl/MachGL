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

			private:
				MACH_RENDERER_3D m_renderer;
				GLuint			 m_fbo;
				GLuint			 m_rbo;
				GLuint			 m_textureColorBuffer;
				float			 m_size;
				WindowDimension  m_windowDimension;
				matrix4x4		 m_projection;
				float3			 m_position;

			public:
				EnvironmentMap(const float& size, const WindowDimension& windowDimension);
				void capture();
				void stop();
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, Object::Camera& camera, const MACH_SHADER& shader);
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, Object::Camera& camera, const MACH_SHADER& shader, const sPoint<Object::Skybox>& skybox);
				const GLuint& getEnvironmentMap() const { return m_textureColorBuffer; }
			private:
				void init();
		};
	}
}
