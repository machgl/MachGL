/*

Mach::GL (Alpha)

*/

#include "../../../Headers/API/Vulkan/VulkanShader.h"

namespace MachGL {
	namespace Graphics {

		VulkanShader::VulkanShader(VkDevice& device) {

			m_device = &device;
		}

		VulkanShader::~VulkanShader() {


		}
	}
}
