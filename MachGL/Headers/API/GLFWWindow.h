#pragma once

#include "../Core/Window.h"

namespace MachGL {

	class GLFWWindow : public Window {

		private:
			GLFWWindow* m_window;
		public:
			GLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height);
	};
}
