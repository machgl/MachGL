#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "Shader.h"
#include "../Plane/Plane.h"
#include "../Maths/Vector.h"

namespace MachGL {
	namespace Graphics {

		class Renderer2D {

			public:
            
                static sPoint<Renderer2D> createRenderer();
            
				Renderer2D()  = default;
				~Renderer2D() = default;

				/// <summary>
				/// Submits a list of planes for rendering and renders them. 
				///	<param name="planes">List of planes to send to renderer.</param>
				/// </summary>
				void submit(const std::vector<Plane::MACH_PLANE>& planes);
				void submit(const Plane::MACH_PLANE& plane);

			protected:
				virtual void flush(const Plane::MACH_PLANE& plane) = 0;
		};
    
        using MACH_RENDERER_2D = sPoint<Renderer2D>;
	}
}
