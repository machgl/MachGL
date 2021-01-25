#pragma once

#include "../../Headers/Core/Includes.h"

namespace MachGL {
	namespace Graphics {

		class Buffer {

			private: 
				GLuint m_bufferID;
				GLuint m_componentCount;
			public:
				Buffer(GLfloat* data, const GLsizei& size, const GLuint& componentCount);
				Buffer(GLuint* data, const GLsizei& size, const GLuint& componentCount);
				~Buffer();
				void bind() const;
				void unbind() const;
				inline const GLuint& getComponentCount() const { return m_componentCount; }
		};
	}
}
