/*

Mach::GL (Alpha)

*/

#include "../../Headers/API/GLFWWindow.h"

namespace MachGL {
    
    GLFWWindow::GLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height) {
        
        m_title = title;
        m_width = (int)width;
        m_height = (int)height;
        m_icons[0] = GLFWimage();
    }
    
    Window::~Window() {
        
        glfwTerminate();
    }

    void GLFWWindow::init() {
        
        m_previousTime = glfwGetTime();
        m_frameCount = 0;

        for (auto i : m_keys) i = false;
        for (auto i : m_mouseButtons) i = false;
        
        #if defined(MACH_VALID_PLATFORM)
            if (!glfwInit()) {
                
                MACH_ERROR_MSG("GLFW failed to initilize");
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
            MACH_ERROR_MSG("Window failed to create");
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
                MACH_ERROR_MSG("Could not initilize OpenGL");
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
        
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_keys[key] = action != GLFW_RELEASE;
        });
        
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_mouseButtons[button] = action != GLFW_RELEASE;
        });
        
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            MACH_CLOSE();
        });
        
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos;
        });
        
        std::cout << "Mach::GL Version: " << MACH_GET_VERSION() << " | OpenGL Version: " << glGetString(GL_VERSION) << " | Graphics Card: " << glGetString(GL_RENDERER)<< std::endl;

        if (m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_splashImage = Graphics::Image::createImage("../MachGL/CoreAssets/CoreTextures/splash.png", Graphics::ImageType::RGBA);
        m_splashScreen = make_sPoint<Splash>(this->getWindowDimension(), m_splashImage);
    }

    void GLFWWindow::update() {
        
        if (m_window == nullptr) {

            MACH_ERROR_MSG("Window is not initilized, make sure you call init()");
            return;
        }

        checkOpenGLError();

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

    void GLFWWindow::clear() {

        if (m_window == nullptr) {

            MACH_ERROR_MSG("Window is not initilized, make sure you call init()");
            return;
        }

        glViewport(0, 0, m_width, m_height);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool GLFWWindow::closed() const {  return glfwWindowShouldClose(m_window) == 1; }
}
