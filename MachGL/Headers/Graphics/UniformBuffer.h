/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Shader.h"

namespace MachGL {
	namespace Graphics {

		class UniformBuffer {

			protected: 
				uint32_t m_currentBufferSize = 0;
				uint32_t m_UBO = 0;
				uint32_t m_binding = 0;

			public:
				static sPoint<UniformBuffer> createUniformBuffer(const uint32_t& size, const uint32_t& binding);
				UniformBuffer() = default;
				~UniformBuffer() = default;
				virtual void setData(const void* data, const uint32_t& size, const uint32_t& offset = 0) = 0;
				virtual void bind() = 0;
				virtual void unbind() = 0;
				virtual void configureUBO(const MACH_SHADER& shader, const std::string& name) = 0;
				
				template<typename T> void pushToBuffer(const T& data) {

					setData(&data, sizeof(data), m_currentBufferSize);
					m_currentBufferSize += sizeof(data);
				}
		};

		class ShaderStorageBuffer {

			protected:
				uint32_t m_currentBufferSize = 0;
				uint32_t m_SSBO;
				uint32_t m_binding;

			public:
				static sPoint<ShaderStorageBuffer> createShaderStorageBuffer(const uint32_t& size, const uint32_t& binding);
				ShaderStorageBuffer() = default;
				~ShaderStorageBuffer() = default;
				virtual void setData(const void* data, const uint32_t& size, const uint32_t& offset = 0) = 0;
				virtual void bind() = 0;
				virtual void unbind() = 0;
				virtual void configureSSBO(const MACH_SHADER& shader, const std::string& name) = 0;

				template<typename T> void pushToBuffer(const T& data) {

					setData(&data, sizeof(data), m_currentBufferSize);
					m_currentBufferSize += sizeof(data);
				}
		};

		using MACH_UNIFORM_BUFFER = sPoint<UniformBuffer>;
		using MACH_SHADER_STORAGE_BUFFER = sPoint<ShaderStorageBuffer>;
	}
}
