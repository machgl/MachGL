/*

Mach::GL (Alpha)


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Object/Object.h"
#include "Shader.h"

namespace MachGL {
	namespace Graphics {

		struct Submittable3D {

			sPoint<Object::Object> object;
			sPoint<Shader>		   shader;
		};
	}
}
