#pragma once

#define MACH_GL_VERSION "0.3 (ALPHA)"

//Platform detection
#if defined(_WIN64) || defined(_WIN32)
    #define MACH_PLATFORM_WINDOWS
    #include "../../Vendor/Glad/include/glad/glad.h"
#elif defined(__APPLE__) || defined(__MACH__)
    #define GL_SILENCE_DEPRECATION
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "ERROR: iOS simulator not supported"
    #elif TARGET_OS_IPHONE
        #define MACH_PLATFORM_IOS
        #error "ERROR: iOS not supported"
    #elif TARGET_OS_MAC == 1
        #define MACH_PLATFORM_MAC
        #define GLFW_INCLUDE_GLCOREARB
        #include <OpenGL/gl3.h>
    #else
        #error "ERROR: Unknown/unsupported Apple platform"
    #endif
#elif defined(__ANDROID__)
    #define MACH_PLATFORM_ANDROID
    #error "ERROR: Android not supported"
#elif defined(__LINUX__)
    #define MACH_PLATFORM_LINUX
    #error "ERROR: Linux not supported"
#else
    #define MACH_PLATFORM_UNKNOWN
    #error "Unknown platform"
#endif

//Checks if the platform is valid
#if defined(MACH_PLATFORM_WINDOWS) || defined(MACH_PLATFORM_MAC)
    #define MACH_VALID_PLATFORM
#endif


