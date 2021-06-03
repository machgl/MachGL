#include "../../Headers/Core/Window.h"
#include "../../Headers/API/GLFWWindow.h"

namespace MachGL {

    bool Window::m_keys[MAX_KEYS];
    bool Window::m_mouseButtons[MAX_BUTTONS];
    double Window::mx;
    double Window::my;

    MACH_WINDOW Window::createWindow(const std::string& title, const float& width, const float& height) {
        
        switch(MACH_GRAPHICS_API) {
                
            case GraphicsAPI::MACH_OpenGL: return make_sPoint<GLFWWindow>(title, width, height);
            default: return make_sPoint<GLFWWindow>(title, width, height);
        }   
    }

    void Window::checkOpenGLError() {

        GLenum errorCode;

        while ((errorCode = glGetError()) != GL_NO_ERROR) {

            std::string error;

            switch (errorCode) {

                case GL_INVALID_ENUM: error = "INVALID ENUM"; break;
                case GL_INVALID_VALUE: error = "INVALID VALUE"; break;
                case GL_INVALID_OPERATION: error = "INVALID OPERATION"; break;
                case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID FRAMEBUFFER OPERATION"; break;
                #if defined(MACH_PLATFORM_WINDOWS)
                    case GL_STACK_OVERFLOW: error = "STACK OVERFLOW"; break;
                    case GL_STACK_UNDERFLOW: error = "STACK UNDERFLOW"; break;
                    case GL_CONTEXT_LOST: error = "CONTEXT LOST"; break;
                #endif
            }

            MACH_ERROR_MSG("OpenGL Error: " + error + " (" + std::to_string(errorCode) + ")");
        }
    }

    bool Window::isKeyPressed(unsigned int keycode) {

        if (keycode >= MAX_KEYS) return false;

        return m_keys[keycode];
    }

    bool Window::isMouseButtonPressed(unsigned int button) {

        if (button >= MAX_BUTTONS) return false;

        return m_mouseButtons[button];
    }

    void Window::getMousePosition(float2& position) {

        position.x = (float)mx;
        position.y = (float)my;
    }
    
    const WindowDimension Window::getWindowDimension() const {

        WindowDimension dimension;
        dimension.width = m_width / (uint32_t)m_xScale;
        dimension.height = m_height / (uint32_t)m_yScale;
        return dimension;
    }

}
