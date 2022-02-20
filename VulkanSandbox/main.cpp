//#define FULLSCREEN

#if defined(FULLSCREEN)

#define WIDTH (uint32_t) 3840
#define HEIGHT (uint32_t) 2160

#else
#define WIDTH (uint32_t) 1920
#define HEIGHT (uint32_t) 1080
#endif

#include "../MachGL/MachGL.h"

using namespace MachGL;

int main() {

	GraphicsAPI::setGraphicsAPI(GraphicsAPI::API::MACH_VULKAN);

	MACH_WINDOW window = Window::createWindow("Vulkan Test", WIDTH, HEIGHT);
	//window->debug();
	window->init();

	while (!window->closed()) {

		if (window->isKeyPressed(GLFW_KEY_ESCAPE)) MACH_CLOSE();

		window->update();
	}

	window->close();

	return 0;
}

