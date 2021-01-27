#pragma once

#include "../../Headers/Core/DataStructures.h"
#include "../../Headers/Core/Includes.h"
#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/Buffer.h"
#include "Shader.h"
#include "Plane.h"
#include "../../Headers/Maths/Vector.h"

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(Vertex)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICIES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

namespace MachGL {
	namespace Graphics {

		class Renderer2D {

			private: 
				GLuint m_VAO;
				GLuint m_VBO;
				Vertex* m_buffer;
				IndexBuffer* m_IBO;
				int m_vertexSize = 4;
				int m_indexSize = 6;
				int m_indexCount;
				std::vector<GLuint> m_textureSlots;
				GLushort m_indicies[RENDERER_INDICIES_SIZE];

				void init();
			public:
				Renderer2D();
				~Renderer2D();

				void begin();
				void submit(const std::unique_ptr<Plane>& plane);
				void flush();
				void end();
		};
	}
}