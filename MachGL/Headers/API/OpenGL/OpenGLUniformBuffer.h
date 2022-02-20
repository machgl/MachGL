/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Graphics/UniformBuffer.h"

namespace MachGL {
	namespace Graphics {

		class OpenGLUniformBuffer : public UniformBuffer {

			public:
				OpenGLUniformBuffer(const uint32_t& size, const uint32_t& binding);
				~OpenGLUniformBuffer();

				virtual void setData(const void* data, const uint32_t& size, const uint32_t& offset = 0) override;
				virtual void bind() override;
				virtual void unbind() override;
				virtual void configureUBO(const MACH_SHADER& shader, const std::string& name) override;
		};

		class OpenGLShaderStorageBuffer : public ShaderStorageBuffer {

			public: 
				OpenGLShaderStorageBuffer(const uint32_t& size, const uint32_t& binding);
				~OpenGLShaderStorageBuffer();

				virtual void setData(const void* data, const uint32_t& size, const uint32_t& offset = 0) override;
				virtual void bind() override;
				virtual void unbind() override;
				virtual void configureSSBO(const MACH_SHADER& shader, const std::string& name) override;
		};
	}
}

