#pragma once

#include "Includes.h"

/// <summary>
/// Defines all of the data types and structures used in the core game engine.
/// </summary>

using float2 = glm::vec2;
using float3 = glm::vec3;
using float4 = glm::vec4;
using matrix4x4 = glm::mat4x4;

typedef SimplexNoise Noise;

struct Vertex {

    float3 vertex;
    float2 uv;
    float3 normal;
    float tid;
    uint32_t color;
    float shine;
    float reflectivity;
    float textureScale;
};

struct Index {

    GLushort index;
};

struct WindowDimension {

    uint32_t width, height;
};

namespace MachGL {

    /// <summary>
    /// Renames std::unique_pointer<T> to MachGL::uPoint<T>.
    /// </summary>
    template<typename T> using uPoint = std::unique_ptr<T>;

    /// <summary>
    /// Renames std::make_unique<T> to MachGL::make_uPoint<T>.
    /// </summary>
    template<typename T, typename ... Args> constexpr uPoint<T> make_uPoint(Args&& ... args) {

        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    /// <summary>
    /// Renames std::shared_pointer<T> to MachGL::sPoint<T>.
    /// </summary>
    template<typename T> using sPoint = std::shared_ptr<T>;

    /// <summary>
    /// Renames std::make_shared<T> to MachGL::make_sPoint<T>.
    /// </summary>
    template<typename T, typename ... Args> constexpr sPoint<T> make_sPoint(Args&& ... args) {

        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    /// <summary>
    /// Gets the version of the Mach::GL engine as an std::string.
    /// </summary>
    /// <returns>std::string of the Mach::GL version.</returns>
    static std::string MACH_GET_VERSION() {

        return MACH_GL_VERSION;
    }

    /// <summary>
    /// Terminates the Mach::GL environment and window.
    /// </summary>
    static void MACH_CLOSE() {

        glfwTerminate();
        exit(0);
    }

    /// <summary>
    /// Prints an error message to the console.
    /// </summary>
    /// <param name="error">Error message to be printed by the console.</param>
    static void MACH_ERROR_MSG(const std::string& error) {
        std::cout << "MACH::GL ERROR: " << error << std::endl;
    }
}
