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
				static float radians(const float& degrees) {
					return glm::radians(degrees);
				}
				static float degrees(const float& radians) {
					return glm::degrees(radians);
				}
		};
	}
}
