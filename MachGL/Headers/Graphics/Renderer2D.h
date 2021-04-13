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

				/// <summary>
				/// Submits a list of planes for rendering and renders them. 
				///	<param name="planes">List of planes to send to renderer.</param>
				/// </summary>
				void submit(const std::vector<Plane::Plane>& planes);
				void submit(const Plane::Plane& plane);

			private:
				void flush(const Plane::Plane& plane);
		};
	}
}