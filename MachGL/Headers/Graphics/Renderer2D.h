#pragma once

#include "../../Headers/Core/DataStructures.h"
#include "../../Headers/Core/Includes.h"
#include "Shader.h"
#include "Plane.h"
#include "../../Headers/Maths/Vector.h"

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
				void submit(const std::vector<Plane>& planes);

			private:
				void begin(const Plane& plane);
				void flush(const Plane& plane);
				void end(const Plane& plane);
				void render(const Plane& plane);
		};
	}
}