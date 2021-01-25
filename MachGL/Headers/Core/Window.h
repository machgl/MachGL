#pragma once

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

#include "Includes.h"
#include "DataStructures.h"
#include "../../Headers/Screens/Splash.h"
#include "../../Headers/Graphics/Image.h"
#include "../../Headers/Utilities/Timer.h"

namespace MachGL {

    class Window {

    private:
        const char* m_title;
        int m_width, m_height;
        int m_aa = 0;
        GLFWwindow* m_window = nullptr;
        Splash* m_splashScreen = nullptr;
        Graphics::Image m_splashImage;
        bool m_vsync = false;
        bool m_fullscreen = false;
        double previousTime = 0;
        int frameCount = 0;
        static bool m_keys[MAX_KEYS];
        static bool m_mouseButtons[MAX_BUTTONS];
        static double mx, my;
        bool m_isLoaded = false;
        bool m_cursor = true;
        bool m_debug = false;
        Timer m_timer;
        const char* m_iconPath = "MachGL/CoreAssets/CoreTextures/defaultIcon.png";
        GLFWimage m_icons[1];

    public:

        /// <summary>
        /// Creates and initilizes a window.
        /// </summary>
        /// <param name="title">Title of window</param>
        /// <param name="width">Horizonal resolution</param>
        /// <param name="height">Vertical resolution</param>
        /// <param name="vsync">V-Sync on (true) or off (false)</param>
        Window(const char* title, const float& width, const float& height);

        ~Window();

        /// <summary>
        /// Enables v-sync
        /// </summary>
        void vsync() { m_vsync = true; };

        /// <summary>
        /// Enables MSAA
        /// </summary>
        /// <param name="aa">MSAA multiplier</param>
        void MSAA(const int& aa) { m_aa = aa; }

        /// <summary>
        /// Enables fullscreen mode
        /// </summary>
        void fullscreen() { m_fullscreen = true; }

        /// <summary>
        /// Disables the cursor for infinite mouse movement, ie. for a mouse based camera system
        /// </summary>
        void disableCursor() { m_cursor = false; }

        /// <summary>
        /// Enables OpenGL degub mode for more information on OpenGL errors
        /// </summary>
        void debug() { m_debug = true; }

        /// <summary>
        /// Initilizes the window.
        /// </summary>
        void init();

        /// <summary>
        /// Clears the color and depth buffer (OpenGL) and enables GL_DEPTH_TEST.
        /// This should be called at the START of the main loop (before any drawing to the screen).
        /// </summary>
        void clear();

        /// <summary>
        /// This updates the screen and swaps the buffers. 
        /// This should be the last function to be called in the main loop.
        /// </summary>
        void update();

        /// <summary>
        /// Checks if the window has been closed. Returns a boolean.
        /// </summary>
        /// <returns></returns>
        bool closed() const;

        /// <summary>
        /// Checks if the key specified has been pressed. Returns a boolean.
        /// </summary>
        /// <param name="keycode">Requied a GLFW keycode. eg. GLFW_KEY_W</param>
        /// <returns>True or false</returns>
        static bool isKeyPressed(unsigned int keycode);

        /// <summary>
        /// Checks if the mouse button specified has been pressed. Returns a boolean.
        /// </summary>
        /// <param name="keycode">Requied a GLFW keycode. eg. GLFW_MOUSE_BUTTON_1 (left mouse button)</param>
        /// <returns>True or false</returns>
        static bool isMouseButtonPressed(unsigned int button);

        /// <summary>
        /// Returns a 2D vector of the mouse position. 
        /// </summary>
        /// <param name="position">Requires a float2 to edit</param>
        static void getMousePosition(float2& position);

        /// <summary>
        /// Callback function for keyboard input. Designed for the GLFW function glfwSetKeyCallback
        /// </summary>
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        /// <summary>
        /// Callback function for mouse button input. Designed for the GLFW function glfwSetMouseButtonCallback
        /// </summary>
        static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

        /// <summary>
        /// Callback function for mouse position. Designed for the GLFW function glfwSetCursorPosCallback
        /// </summary>
        static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);

        /// <summary>
        /// Sets the window to a loaded state (Stops the splash screen).
        /// </summary>
        inline void windowLoaded() { m_isLoaded = true; }

        /// <summary>
        /// Checks if the windowLoaded function has been called. 
        /// </summary>
        /// <returns>True or false</returns>
        inline const bool& isWindowLoaded() const { return m_isLoaded; }

        /// <summary>
        /// Returns the horizontal resolution of the window (int).
        /// </summary>
        /// <returns>True or false</returns>
        inline const int& getWidth() const { return m_width; }

        /// <summary>
        /// Returns the vertical resolution of the window (int).
        /// </summary>
        /// <returns>True or false</returns>
        inline const int& getHeight() const { return m_height; }

        /// <summary>
        /// Sets the icon for the window, defaults to the Mach::GL logo.
        /// </summary>
        /// <param name="file">Filepath of the icon</param>
        void setIcon(const char* file) { m_iconPath = file; };
    };
}


