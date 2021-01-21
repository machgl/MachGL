#pragma once

#include "Includes.h"

namespace MachGL {

	std::string MachGLGetVersion() {

		return MACH_GL_VERSION;
	}

	void MachGLClose() {

		glfwTerminate();
		exit(0);
	}
}
