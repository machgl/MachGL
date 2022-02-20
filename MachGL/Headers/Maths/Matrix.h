/*

Mach::GL (Alpha) 


*/

#include "MachPCH.h"
#include "../Core/DataStructures.h"

#pragma once

namespace MachGL {
	namespace Maths {

		class Matrix {

			public:

				/// <summary>
				/// Generates a 4x4 perspective projection matrix.
				/// </summary>
				/// <param name="fov">Field of view.</param>
				/// <param name="windowDimension">WindowDimension object.</param>
				/// <param name="near">Start of the projection frustum closest to the camera.</param>
				/// <param name="far">End of the projection frustum (render distance).</param>
				/// <returns>4x4 perspective projection matrix.</returns>
				static matrix4x4 perspective(const float& fov, const WindowDimension& windowDimension, const float& near, const float& far) {
					return glm::perspective(fov, (float)windowDimension.width / (float)windowDimension.height, near, far);
				}

				static void printMatrix(const matrix4x4& matrix) {

					for (uint32_t r = 0; r < 4; r++) {
						for (uint32_t c = 0; c < 4; c++) {

							if (c == 3 && r == 3) std::cout << matrix[r][c];
							else  std::cout << matrix[r][c] << ", ";
						}
						std::cout << std::endl;
					}
				}

				/// <summary>
				/// Generates a 4x4 orthographic projection matrix.
				/// </summary>
				/// <param name="left">Left hand side of the projection.</param>
				/// <param name="right">Right hand side of the projection.</param>
				/// <param name="top">Top of the projection.</param>
				/// <param name="bottom">Bottom of the projection.</param>
				/// <param name="near">Start of the projection frustum closest to the camera.</param>
				/// <param name="far">End of the projection frustum (render distance).</param>
				/// <returns>4x4 orthographic projection matrix.</returns>
				static matrix4x4 orthographic(const float& left, const float& right, const float& top, const float& bottom,
					const float& near, const float& far) {
					return glm::ortho(left, right, bottom, top, near, far);
				}

				/// <summary>
				/// Generates a perspective projection matrix based on a desired FOV and the size of the window.
				/// </summary>
				/// <param name="fov">Field of view.</param>
				/// <param name="windowDimension">WindowDimension object.</param>
				/// <returns>4x4 perspective projection matrix.</returns>
				static matrix4x4 simplePerspective(const float& fov, const WindowDimension& windowDimension) {
					return perspective(fov, windowDimension, 0.1f, 1000.0f);
				}

				/// <summary>
				/// Generates a orthographic projection matrix based on the size of the window.
				/// </summary>
				/// <param name="windowDimension">WindowDimension obejct.</param>
				/// <returns>4x4 orthographic projection matrix.</returns>
				static matrix4x4 simpleOrthographic(const WindowDimension& windowDimension) {
					return orthographic(0, (float)windowDimension.width, 0, (float)windowDimension.height, -1.0f, 1.0f);
				}

				/// <summary>
				/// Generates a "lookAt" camera matrix. 
				/// </summary>
				/// <param name="position">Position coorinates of the camera.</param>
				/// <param name="target">Target vector of the camera.</param>
				/// <param name="up">Up vector fromt the camera.</param>
				/// <returns>4x4 camera matrix.</returns>
				static matrix4x4 lookAt(const float3& position, const float3& target, const float3& up) {
					return glm::lookAt(position, target, up);
				}
		};
	}
}