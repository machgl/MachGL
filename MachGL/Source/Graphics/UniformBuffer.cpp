/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/UniformBuffer.h"
#include "../../Headers/API/OpenGL/OpenGLUniformBuffer.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Graphics {

		MACH_UNIFORM_BUFFER UniformBuffer::createUniformBuffer(const uint32_t& size, const uint32_t& binding) {

			switch (GraphicsAPI::getGraphicsAPI()) {

				case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLUniformBuffer>(size, binding);
				default: return make_sPoint<OpenGLUniformBuffer>(size, binding);
			}
		}

		MACH_SHADER_STORAGE_BUFFER ShaderStorageBuffer::createShaderStorageBuffer(const uint32_t& size, const uint32_t& binding) {

			switch (GraphicsAPI::getGraphicsAPI()) {

				case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLShaderStorageBuffer>(size, binding);
				default: make_sPoint<OpenGLShaderStorageBuffer>(size, binding);
			}
		}
	}
}
