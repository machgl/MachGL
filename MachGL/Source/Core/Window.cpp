#include "../../Headers/Core/Window.h"

namespace MachGL {

    bool Window::m_keys[MAX_KEYS];
    bool Window::m_mouseButtons[MAX_BUTTONS];
    double Window::mx;
    double Window::my;

    #if defined(MACH_PLATFORM_WINDOWS)
        void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                type, severity, message);
        }
    #endif

    Window::Window(const std::string& title, const float& width, const float& height)
        : m_title(title), m_width((int)width), m_height((int)height) {

        m_icons[0] = GLFWimage();
    }

    Window::~Window() {

        glfwTerminate();
    }

    void Window::init() {

        previousTime = glfwGetTime();
        frameCount = 0;

        for (auto i : m_keys) {

            i = false;
        }

        for (auto i : m_mouseButtons) {

            i = false;
        }

        #if defined(MACH_VALID_PLATFORM)
            if (!glfwInit()) {

                std::cout << "GLFW failed to initilize" << std::endl;
                return;
            }
        #endif

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

        #if defined(MACH_PLATFORM_MAC)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #elif defined(MACH_PLATFORM_WINDOWS)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        #endif

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, m_aa);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        if (m_fullscreen) m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
        else m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

        if (!m_window) {

            glfwTerminate();
            std::cout << "Window failed to create" << std::endl;
            return;
        }

        if (!m_cursor) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       
        m_icons[0].pixels = stbi_load(m_iconPath.c_str(), &m_icons[0].width, &m_icons[0].height, 0, 4);
        glfwSetWindowIcon(m_window, 1, m_icons);
        stbi_image_free(m_icons[0].pixels);

        glfwMakeContextCurrent(m_window);

        #if defined(MACH_PLATFORM_WINDOWS)
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

                glfwTerminate();
                std::cout << "Could not initilize OpenGL" << std::endl;
                return;
            }

            if (m_debug) {

                glEnable(GL_DEBUG_OUTPUT);
                glDebugMessageCallback(MessageCallback, 0);
            }
        #endif

        glfwGetFramebufferSize(m_window, (int*)&m_width, (int*)&m_height);
        glViewport(0, 0, m_width, m_height);
        #if defined(MACH_PLATFORM_MAC)
         glfwGetWindowContentScale(m_window, &m_xScale, &m_yScale);
        #endif
        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowUserPointer(m_window, this);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetMouseButtonCallback(m_window, mouseButton_callback);
        glfwSetCursorPosCallback(m_window, cursor_position_callback);
        std::cout << "Mach::GL Version: " << MACH_GET_VERSION() << " | OpenGL Version: " << glGetString(GL_VERSION) << " | Graphics Card: " << glGetString(GL_RENDERER)<< std::endl;

        if (m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);


        m_splashImage = Graphics::Image("MachGL/CoreAssets/CoreTextures/splash.png", Graphics::ImageType::RGBA);
        m_splashScreen = make_sPoint<Splash>(this->getWindowDimension(), m_splashImage.ref());
    }

    void Window::clear() {

        if (m_window == nullptr) {

            std::cout << "Window is not initilized, make sure you call init()" << std::endl;
            return;
        }

        glViewport(0, 0, m_width, m_height);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool Window::closed() const {  return glfwWindowShouldClose(m_window) == 1; }

    void Window::update() {

        if (m_window == nullptr) {

            std::cout << "Window is not initilized, make sure you call init()" << std::endl;
            return;
        }

        GLenum error = glGetError();

        if (error != GL_NO_ERROR) std::cout << "OpenGL error: " << error << std::endl;

        if (m_aa) glEnable(GL_MULTISAMPLE);

        if (!m_isLoaded) {
            if (m_timer.elapsedTimeSeconds() > 2) {

                m_splashScreen->setAlpha(3 - (float)m_timer.elapsedTimeSeconds());
            }

            m_splashScreen->render();
        }

        if (m_timer.elapsedTimeSeconds() > 3) {

            windowLoaded();
            m_timer.~Timer();
        }

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    bool Window::isKeyPressed(unsigned int keycode) {

        if (keycode >= MAX_KEYS) return false;

        return m_keys[keycode];
    }

    bool Window::isMouseButtonPressed(unsigned int button) {

        if (button >= MAX_BUTTONS) return false;

        return m_mouseButtons[button];
    }

    void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->m_keys[key] = action != GLFW_RELEASE;
    }

    void Window::mouseButton_callback(GLFWwindow* window, int button, int action, int mods) {

        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->m_mouseButtons[button] = action != GLFW_RELEASE;
    }

    void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->mx = xpos;
        win->my = ypos;
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