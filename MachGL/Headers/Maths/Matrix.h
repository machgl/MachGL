/*

Mach::GL (Alpha) 


*/

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"

#pragma once

namespace MachGL {
	namespace Maths {

		class Matrix {

			public:

				static matrix4x4 projection(const float& fov, const WindowDimension& windowDimension, const float& near, const float& far) {
					float aspectRatio = (float)windowDimension.width / (float)windowDimension.height;
					return glm::perspective(fov, aspectRatio, near, far);
				}

				static matrix4x4 orthographic(const float& left, const float& right, const float& top, const float& bottom,
					const float& near, const float& far) {
					return glm::ortho(left, right, bottom, top, near, far);
				}

				static matrix4x4 simpleProjection(const float& fov, const WindowDimension& windowDimension) {
					return projection(fov, windowDimension, 0.1f, 1000.0f);
				}

				static matrix4x4 simpleOrthographic(const WindowDimension& windowDimension) {
					return orthographic(0, (float)windowDimension.width, 0, (float)windowDimension.height, -1.0f, 1.0f);
				}

				static matrix4x4 lookAt(const float3& position, const float3& target, const float3& up) {
					return glm::lookAt(position, target, up);
				}
		};
	}
}