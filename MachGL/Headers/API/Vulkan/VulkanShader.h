/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Graphics/Shader.h"

namespace MachGL {
	namespace Graphics {

		class VulkanShader : public Shader {

			private: 
				VkShaderModule m_shader;
				VkDevice* m_device;

			public:
				VulkanShader(VkDevice& device);
				~VulkanShader();
		};
		
	}
}
