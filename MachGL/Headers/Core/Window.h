#pragma once

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

#include "Includes.h"
#include "DataStructures.h"
#include "../Screens/Splash.h"
#include "../Graphics/Image.h"
#include "../Utilities/Timer.h"

namespace MachGL {

    class Window {
   
        protected:
            std::string          m_title;
            uint32_t             m_width, m_height;
            uint32_t             m_aa            = 0;
            MACH_SPLASH          m_splashScreen  = nullptr;
            Graphics::MACH_IMAGE m_splashImage;
            bool                 m_vsync         = false;
            bool                 m_fullscreen    = false;
            double               m_previousTime  = 0;
            int                  m_frameCount    = 0;
            static bool          m_keys[MAX_KEYS];
            static bool          m_mouseButtons[MAX_BUTTONS];
            static double        mx, my;
            bool                 m_isLoaded      = false;
            bool                 m_cursor        = true;
            bool                 m_debug         = false;
            Timer                m_timer;
            std::string          m_iconPath      = "MachGL/CoreAssets/CoreTextures/defaultIcon.png";
            float                m_xScale        = 1;
            float                m_yScale        = 1;

        public:
            static sPoint<Window> createWindow(const std::string& title, const uint32_t& width, const uint32_t& height);
            
            Window() = default;
        
            virtual ~Window() = 0;

            /// <summary>
            /// Enables v-sync
            /// </summary>
            void vsync() { m_vsync = true; };

            /// <summary>
            /// Enables MSAA
            /// </summary>
            /// <param name="aa">MSAA multiplier</param>
            void MSAA(const uint32_t& aa) { m_aa = aa; }

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
            virtual void init() = 0;

            /// <summary>
            /// Clears the color and depth buffer (OpenGL) and enables GL_DEPTH_TEST.
            /// This should be called at the START of the main loop (before any drawing to the screen).
            /// </summary>
            virtual void clear() = 0;

            /// <summary>
            /// This updates the screen and swaps the buffers. 
            /// This should be the last function to be called in the main loop.
            /// </summary>
            virtual void update() = 0;

            /// <summary>
            /// Checks if the window has been closed. Returns a boolean.
            /// </summary>
            /// <returns></returns>
            virtual bool closed() const = 0;;

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
            inline const uint32_t& getWidth() const { return m_width; }

            /// <summary>
            /// Returns the vertical resolution of the window (int).
            /// </summary>
            /// <returns>True or false</returns>
            inline const uint32_t& getHeight() const { return m_height; }

            /// <summary>
            /// Sets the icon for the window, defaults to the Mach::GL logo.
            /// </summary>
            /// <param name="file">Filepath of the icon</param>
            inline void setIcon(const std::string& file) { m_iconPath = file; };

            /// <summary>
            /// Gets the dimensions of the window as a WindowDimension struct.
            /// </summary>
            /// <returns>WindowDimension struct of the window dimensions.</returns>
            const WindowDimension getWindowDimension() const;
        
        protected:
            void checkOpenGLError();
    };

    using MACH_WINDOW = sPoint<Window>;
}


