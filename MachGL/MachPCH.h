/*

Mach::GL (Alpha) 


*/

#define GLFW_INCLUDE_VULKAN

#pragma once

//Platform detection

#include "Headers/Core/PlatformDetection.h"

//Standard library includes

#include <algorithm>
#include <filesystem>
#include <math.h>
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <strstream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <chrono>
#include <random>
#include <numeric>
#include <memory>
#include <unordered_map>
#include <future>
#include <mutex>
#include <map>
#include <optional>

//External vendor includes

#include "../../Vendor/glfw/include/GLFW/glfw3.h"
#include "../../Vendor/glm/glm/glm.hpp"
#include "../../Vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../Vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../Vendor/glm/glm/gtx/rotate_vector.hpp"
#include "../../Vendor/SimplexNoise/include/SimplexNoise.h"
#include "../../Vendor/yaml-cpp/include/yaml-cpp/yaml.h"
#include "../../Vendor/fast_obj.h"
#include "../../Vendor/Vulkan/Include/shaderc/shaderc.hpp"
#include "../../Vendor/Vulkan/Include/spirv_cross/spirv_cross.hpp"
#include "../../../Vendor/Vulkan/Include/spirv_cross/spirv_glsl.hpp"
#include "../../Vendor/HazelAudio/HazelAudio/vendor/OpenAL-Soft/include/AL/al.h"
#include "../../Vendor/HazelAudio/HazelAudio/vendor/OpenAL-Soft/include/AL/alc.h"
#include "../../Vendor/HazelAudio/HazelAudio/vendor/OpenAL-Soft/include/AL/alc.h"
