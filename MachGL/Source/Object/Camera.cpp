#include "../../Headers/Object/Camera.h"

namespace MachGL {
	namespace Object {

		Camera::Camera(const float3& position, const CameraType& cameraType, const MACH_WINDOW& window) : m_pos(position), m_cameraType(cameraType), m_window(window) {

			m_originalPos = m_pos;
			m_originalY = m_originalPos.y;
		}

		MACH_CAMERA Camera::createCamera(const float3& position, const CameraType& cameraType, const MACH_WINDOW& window) {
			return make_sPoint<Camera>(position, cameraType, window);
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

			m_cameraFront = getFront(m_pitch, m_yaw);
		}
		
		matrix4x4 Camera::getViewMatrix() {

			if (m_cameraType == CameraType::FPS) m_pos.y = m_cameraY;
			if (m_cameraType == CameraType::CUBEMAP) return Maths::Matrix::lookAt(m_pos, m_pos + m_cameraFront, m_cameraUp);
			return Maths::Matrix::lookAt(m_pos, m_pos + m_cameraFront, m_cameraUp);
		}

		float3 Camera::getFront(float pitch, float yaw) {

			float3 front;
			front.x = cos(Maths::Functions::radians(yaw - 90)) * cos(Maths::Functions::radians(pitch));
			front.y = sin(Maths::Functions::radians(pitch));
			front.z = sin(Maths::Functions::radians(yaw - 90)) * cos(Maths::Functions::radians(pitch));
			return Maths::Vector::normalize(front);
		}

		matrix4x4 Camera::getViewMatrix(const uint32_t& face) {

			switch (face) {

				case 0:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(0, 90), float3(0, -1, 0));
					break;
				case 1:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(0, -90), float3(0, -1, 0));
					break;
				case 2:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(90, 180), float3(0, 0, 1));
					break;
				case 3:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(-90, 180), float3(0, 0, 1));
					break;
				case 4:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(0, 180), float3(0, -1, 0));
					break;
				case 5:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(0, 0), float3(0, -1, 0));
					break;
				default:
					return Maths::Matrix::lookAt(m_pos, m_pos + getFront(0, 0), float3(0, -1, 0));
					break;
			}
		}
	}
}
