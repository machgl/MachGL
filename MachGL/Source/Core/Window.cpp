/*

Mach::GL (Alpha)

*/

#include "../../Headers/Core/Window.h"
#include "../../Headers/API/GLFWWindow.h"
#include "../../Headers/API/API.h"

namespace MachGL {

    bool Window::m_keys[MAX_KEYS];
    bool Window::m_mouseButtons[MAX_BUTTONS];
    double Window::mx;
    double Window::my;

    MACH_WINDOW Window::createWindow(const std::string& title, const uint32_t& width, const uint32_t& height) {
        
        switch (GraphicsAPI::getGraphicsAPI()) {
                
            case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<GLFWWindow>(title, width, height); break;
            case GraphicsAPI::API::MACH_VULKAN: return make_sPoint<VulkanGLFWWindow>(title, width, height); break;
            default: return make_sPoint<GLFWWindow>(title, width, height); break;
        }   
    }

    void Window::checkOpenALError() {

        ALCenum errorCode;

        while ((errorCode = alGetError()) != AL_NO_ERROR) {

            std::string error;

            switch (errorCode) {

            case AL_INVALID_NAME: error = "INVALID NAME"; break;
            case AL_INVALID_ENUM: error = "INVALID ENUM"; break;
            case AL_INVALID_VALUE: error = "INVALID VALUE"; break;
            case AL_INVALID_OPERATION: error = "INVALID OPERATION"; break;
            case AL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
            }

            MACH_ERROR_MSG("OpenAL Error: " + error + " (" + std::to_string(errorCode) + ")");
        }
    }

    void Window::cleanupOpenAL() {

        m_audioDevice = alcGetContextsDevice(m_audioContext);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_audioContext);
        alcCloseDevice(m_audioDevice);
    }

    void Window::initAudioDevice() {

        if (!(m_audioDevice = alcOpenDevice(NULL))) MACH_ERROR_MSG("OpenAL Error: Failed to initialize audio device");
        if (m_enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_FALSE) MACH_ERROR_MSG("OpenAl Error: Enumeration not supported");

        m_audioContext = alcCreateContext(m_audioDevice, NULL);

        if (!alcMakeContextCurrent(m_audioContext)) MACH_ERROR_MSG("OpenAL Error: Failed to make audio context current");
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
