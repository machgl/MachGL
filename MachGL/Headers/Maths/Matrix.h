/*

Mach::GL (Alpha) 


*/

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"

#pragma once

namespace MachGL {
	namespace Maths {

		class Matrix {

			public:

				static matrix4x4 projection(const float& fov, const float& screenWidth, const float& screenHeight, const float& near, const float& far) {
					float aspectRatio = (float)screenWidth / (float)screenHeight;
					return glm::perspective(fov, aspectRatio, near, far);
				}

				static matrix4x4 orthographic(const float& left, const float& right, const float& top, const float& bottom,
					const float& near, const float& far) {
					return glm::ortho(left, right, bottom, top, near, far);
				}

				static matrix4x4 simpleProjection(const float& fov, const float& screenWidth, const float& screenHeight) {
					return projection(fov, screenWidth, screenHeight, 0.1f, 1000.0f);
				}

				static matrix4x4 simpleOrthographic(const float& screenWidth, const float& screenHeight) {
					return orthographic(0, screenWidth, 0, screenHeight, -1.0f, 1.0f);
				}

				static matrix4x4 lookAt(const float3& position, const float3& target, const float3& up) {
					return glm::lookAt(position, target, up);
				}
		};
	}
}