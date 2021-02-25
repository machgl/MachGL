#pragma once

#include "../Core/DataStructures.h"
#include "../Core/Includes.h"
#include "Shader.h"
#include "../Plane/Plane.h"
#include "../Maths/Vector.h"

namespace MachGL {
	namespace Graphics {

		class Renderer2D {

			public:
				Renderer2D() = default;
				~Renderer2D() = default;
				void submit(const std::vector<Plane::Plane>& planes);

			private:
				void flush(const Plane::Plane& plane);
		};
	}
}