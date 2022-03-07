/*

Mach::GL (Alpha)

*/

#include "../../Headers/API/API.h"

namespace MachGL {

	//Sets the default graphics API to OpenGL & sets the default audio API to OpenAL 

	GraphicsAPI::API GraphicsAPI::s_graphicsAPI = GraphicsAPI::API::MACH_OPEN_GL;
	AudioAPI::API AudioAPI::s_audioAPI = AudioAPI::API::MACH_OPEN_AL;
}
