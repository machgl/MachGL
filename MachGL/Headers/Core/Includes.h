#pragma once

#define MACH_GL_VERSION "1 (ALPHA)"

#if defined(__WIN32__) || defined(__WIN64__) 
    #include "../../Vendor/glad.h"
#endif

#if defined(__APPLE__)
    #define GLFW_INCLUDE_GLCOREARB
    #include <OpenGL/gl3.h>
#endif

#include "../../Vendor/glfw/include/GLFW/glfw3.h"
#include "../../Vendor/glm/glm/glm.hpp"
#include "../../Vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../Vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../Vendor/SimplexNoise.h"
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

