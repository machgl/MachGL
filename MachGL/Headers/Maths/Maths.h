/*

Mach::GL (Alpha) 


*/

#include "Matrix.h"
#include "Vector.h"
#include "Constants.h"

#pragma once

namespace MachGL {
	namespace Maths {

		class Functions {

			public: 

				/// <summary>
				/// Converts angle in degrees into radians. 
				/// </summary>
				/// <param name="degrees">Angle in degrees.</param>
				/// <returns>Angle in radians.</returns>
				static float radians(const float& degrees) {
					return glm::radians(degrees);
				}

				/// <summary>
				/// Converts angle in radians into degrees. 
				/// </summary>
				/// <param name="radians">Angle in radians.</param>
				/// <returns>Angle in degrees.</returns>
				static float degrees(const float& radians) {
					return glm::degrees(radians);
				}
		};
	}
}
