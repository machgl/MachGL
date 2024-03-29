#pragma once

#include "MachPCH.h"
#include "../Core/Window.h"
#include "../Maths/Maths.h"

namespace MachGL {
	namespace Object {
		
		enum class CameraType { FPS, FLY, CUBEMAP };

		class Camera {

			private:
				float3			m_pos				= float3(0, 0, 0);
				float3			m_originalPos		= m_pos;
				float3			m_cameraFront		= float3(0, 0, -1);
				float3			m_cameraUp			= float3(0, 1, 0);
				CameraType		m_cameraType		= CameraType::FPS;
				MACH_WINDOW     m_window			= nullptr;
				float			m_yaw				= 0.0f;
				float			m_pitch				= 0.0f;
				float			m_cameraY			= m_pos.y;
				float			m_originalY			= m_originalPos.y;
				float			m_lastX				= (float)m_window->getWidth() / 2.0f;
				float			m_lastY				= (float)m_window->getHeight() / 2.0f;
				bool			m_firstMouse		= true;
				bool			m_defaults			= true;
				
			public:
				Camera() = default;
				~Camera() = default;
				Camera(const float3& position, const CameraType& cameraType, const MACH_WINDOW& window);
				inline const float3& getPosition() const { return m_pos; }
				inline const float3& getFront() const { return m_cameraFront; }
				inline void avoidDefaults() { m_defaults = false; }
				inline void setYaw(const float& yaw) { m_yaw = yaw; }
				inline void setPitch(const float& pitch) { m_pitch = pitch; }
				inline void setUp(const float3& cameraUp) { m_cameraUp = cameraUp; }
				inline void limitY(const float& cameraY) { m_cameraY = cameraY; }
				inline void reset() { m_pos = m_originalPos; m_cameraY = m_originalY; };
				void moveX(const float& velocity);
				void moveY(const float& velocity);
				void moveZ(const float& velocity);
				void mouseMovement(const float& sensitivity);
				matrix4x4 getViewMatrix();
				matrix4x4 getViewMatrix(const uint32_t& face);
				inline sPoint<Camera> ref() { return make_sPoint<Camera>(*this); }

				static sPoint<Camera> createCamera(const float3& position, const CameraType& cameraType, const MACH_WINDOW& window);

			private:
				float3 getFront(float pitch, float yaw);
		};

		using MACH_CAMERA = sPoint<Camera>;
	}
}
