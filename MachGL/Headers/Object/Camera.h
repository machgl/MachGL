#pragma once

#include "../Core/Window.h"
#include "../Maths/Maths.h"
#include "../Core/Includes.h"

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
				sPoint<Window>  m_window			= nullptr;
				float			m_yaw				= 0.0f;
				float			m_pitch				= 0.0f;
				float			m_cameraY			= m_pos.y;
				float			m_originalY			= m_originalPos.y;
				float			m_lastX				= (float)m_window->getWidth() / 2.0f;
				float			m_lastY				= (float)m_window->getHeight() / 2.0f;
				bool			m_firstMouse		= true;
				bool			m_defaults			= true;
				
			public:
				Camera(const float3& position, const CameraType& cameraType, const sPoint<Window>& window);
				inline const float3& getPosition() const { return m_pos; }
				inline const float3& getFront() const { return m_cameraFront; }
				void avoidDefaults() { m_defaults = false; }
				void setYaw(const float& yaw) { m_yaw = yaw; }
				void setUp(const float3& cameraUp) { m_cameraUp = cameraUp; }
				void limitY(const float& cameraY) { m_cameraY = cameraY; }
				void reset() { m_pos = m_originalPos; m_cameraY = m_originalY; };
				void moveX(const float& velocity);
				void moveY(const float& velocity);
				void moveZ(const float& velocity);
				void mouseMovement(const float& sensitivity);
				void switchToFace(const uint32_t& face);
				void updateViewMatrix();
				matrix4x4 getViewMatrix();
		};
	}
}