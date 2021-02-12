#pragma once

#include "../Core/DataStructures.h"
#include "../Core/Includes.h"
#include "Shader.h"
#include "../Plane/Plane.h"
#include "../Maths/Vector.h"

namespace MachGL {
	namespace Graphics {

		class Renderer2D {

			private: 
				std::vector<GLuint> m_textureSlots;
				Vertex* m_buffer = nullptr;
				Index* m_indexBuffer = nullptr;

			public:
				Renderer2D() = default;
				~Renderer2D();
				void submit(const std::vector<Plane::Plane>& planes);

			private:
				void begin(const Plane::Plane& plane);
				void flush(const Plane::Plane& plane);
				void end(const Plane::Plane& plane);
				void render(const Plane::Plane& plane);
		};
	}
}