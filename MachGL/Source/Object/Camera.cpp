#include "../../Headers/Object/Camera.h"

namespace MachGL {
	namespace Object {

		Camera::Camera(const float3& position, const CameraType& cameraType, Window* window) : m_pos(position), m_cameraType(cameraType), m_window(window) {
		
			m_originalPos = m_pos;
			m_originalY = m_originalPos.y;
		}

		void Camera::moveX(const float& velocity) {
			
			m_pos += velocity * m_cameraFront;
		}

		void Camera::moveY(const float& velocity) {
			
			if (m_cameraType == CameraType::FPS)
				m_cameraY += velocity;
			
			if (m_cameraType == CameraType::FLY)
				m_pos.y += velocity;
		}

		void Camera::moveZ(const float& velocity) {
			
			m_pos += Maths::Vector::normalize(Maths::Vector::crossProduct(m_cameraFront, m_cameraUp)) * velocity;
		}

		void Camera::mouseMovement(const float& sensitivity) {
		
			float2 mousePos;

			m_window->getMousePosition(mousePos);

			if (m_firstMouse) {

				m_lastX = mousePos.x;
				m_lastY = mousePos.y;
				m_firstMouse = false;
			}

			float xOffs = mousePos.x - m_lastX;
			float yOffs = mousePos.y - m_lastY;
			m_lastX = mousePos.x;
			m_lastY = mousePos.y;

			xOffs *= sensitivity;
			yOffs *= sensitivity;

			m_yaw += xOffs;
			m_pitch += yOffs * -1;

			if (m_pitch > 89) m_pitch = 89;
			if (m_pitch < -89) m_pitch = -89;

			float3 front;
			front.x = cos(Maths::Functions::radians(m_yaw)) * cos(Maths::Functions::radians(m_pitch));
			front.y = sin(Maths::Functions::radians(m_pitch));
			front.z = sin(Maths::Functions::radians(m_yaw)) * cos(Maths::Functions::radians(m_pitch));
			m_cameraFront = Maths::Vector::normalize(front);
		}

		matrix4x4 Camera::getViewMatrix() {

			if (m_cameraType == CameraType::FPS) m_pos.y = m_cameraY;

			return Maths::Matrix::lookAt(m_pos, m_pos + m_cameraFront, m_cameraUp);
		}
	}
}