/*

Mach::GL (Alpha)

*/

#include "../../../Headers/API/OpenGL/OpenGLUniformBuffer.h"

namespace MachGL {
	namespace Graphics {

		OpenGLUniformBuffer::OpenGLUniformBuffer(const uint32_t& size, const uint32_t& binding)  {

			m_binding = binding;

			glGenBuffers(1, &m_UBO);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
			unbind();
			glBindBufferRange(GL_UNIFORM_BUFFER, m_binding, m_UBO, 0, size);
		}

		OpenGLUniformBuffer::~OpenGLUniformBuffer() {

			glDeleteBuffers(1, &m_UBO);
		}

		void OpenGLUniformBuffer::configureUBO(const MACH_SHADER& shader, const std::string& name) {

			uint32_t uniformBlockIndex = glGetUniformBlockIndex(shader->getShaderID(), name.c_str());
			glUniformBlockBinding(shader->getShaderID(), uniformBlockIndex, m_binding);
		}

		void OpenGLUniformBuffer::setData(const void* data, const uint32_t& size, const uint32_t& offset) {

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
			unbind();
		}

		void OpenGLUniformBuffer::bind() {

			glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
		}

		void OpenGLUniformBuffer::unbind() {

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		OpenGLShaderStorageBuffer::OpenGLShaderStorageBuffer(const uint32_t& size, const uint32_t& binding) {

			glGenBuffers(1, &m_SSBO);
			bind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_STATIC_DRAW);
			unbind();
			glBindBufferRange(GL_SHADER_STORAGE_BUFFER, m_binding, m_SSBO, 0, size);
		}

		OpenGLShaderStorageBuffer::~OpenGLShaderStorageBuffer() {

			glDeleteBuffers(1, &m_SSBO);
		}

		void OpenGLShaderStorageBuffer::configureSSBO(const MACH_SHADER& shader, const std::string& name) {

			uint32_t uniformBlockIndex = glGetProgramResourceIndex(shader->getShaderID(), GL_SHADER_STORAGE_BUFFER, name.c_str());
			glUniformBlockBinding(shader->getShaderID(), uniformBlockIndex, m_binding);
		}

		void OpenGLShaderStorageBuffer::setData(const void* data, const uint32_t& size, const uint32_t& offset) {

			bind();
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
			unbind();
		}

		void OpenGLShaderStorageBuffer::bind() {

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO);
		}

		void OpenGLShaderStorageBuffer::unbind() {

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}
	}
}
