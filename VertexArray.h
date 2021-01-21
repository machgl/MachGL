#pragma once

#include "Includes.h"
#include "Buffer.h"

namespace MachGL {
	namespace Graphics {

		class VertexArray {

			private: 
				GLuint m_arrayID;
				std::vector<Buffer*> m_buffers;
			public:
				VertexArray();
				~VertexArray();
				void addBuffer(Buffer* buffer, const GLuint& index);
				void bind() const;
				void unbind() const;
		};
	}
}