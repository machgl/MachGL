/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/EnvironmentMap.h"
#include "../../Headers/API/OpenGL/OpenGLEnvironmentMap.h"

namespace MachGL {
	namespace Graphics {

		MACH_ENVIRONMENT_MAP EnvironmentMap::createEnvironmentMap(const float& size, const WindowDimension& windowDimension) {

			switch (MACH_GRAPHICS_API) {

				case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLEnvironmentMap>(size, windowDimension);
				default: return make_sPoint<OpenGLEnvironmentMap>(size, windowDimension);
			}
		}
	}
}
