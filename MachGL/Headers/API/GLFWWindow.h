/*

Mach::GL (Alpha)

*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Core/Window.h"

namespace MachGL {

	class GLFWWindow : public Window {

		private:
			GLFWwindow* m_window;
            GLFWimage m_icons[1];
		public:
			GLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height);
            ~GLFWWindow() = default;
        
            void init() override;
            void update() override;
            void clear() override;
            bool closed() const override;
	};
}
