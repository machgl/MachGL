#pragma once

#define MACH_GL_VERSION "0.2.1 (ALPHA)"

//Platform detection
#if defined(_WIN64) || defined(_WIN32)
    #define MACH_PLATFORM_WINDOWS
    #include "../../Vendor/glad.h"
#elif defined(__APPLE__) || defined(__MACH__) 
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

//Core includes for the engine
#include "../../Vendor/glfw/include/GLFW/glfw3.h"
#include "../../Vendor/glm/glm/glm.hpp"
#include "../../Vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../Vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../Vendor/SimplexNoise.h"
#include "../../Vendor/yaml-cpp/include/yaml-cpp/yaml.h"
#include <math.h>
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <chrono>
#include <random>
#include <numeric>
#include <memory>
#include <unordered_map>

