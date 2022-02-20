/*

Mach::GL (Alpha)


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Object/Object.h"
#include "Shader.h"

namespace MachGL {
	namespace Graphics {

		struct Submittable3D {

			Object::MACH_OBJECT object;
			MACH_SHADER		    shader;
		};
	}
}
