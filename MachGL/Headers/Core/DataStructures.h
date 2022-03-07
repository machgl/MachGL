#pragma once

#include "MachPCH.h"
#define MACH_TEST

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

/// <summary>
/// Defines all of the data types and structures used in the core game engine.
/// </summary>

using float2    = glm::vec2;
using float3    = glm::vec3;
using float4    = glm::vec4;
using matrix4x4 = glm::mat4x4;

typedef SimplexNoise Noise;

struct Vertex {

    float3   vertex;
    float2   uv;
    float3   normal;
    float    tid;
    uint32_t color;
    float    shine;
    float    reflectivity;
    float    textureScale;
};

struct Index {

    GLushort index;
};

struct WindowDimension {

    uint32_t width = 0, height = 0;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {

    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
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
        std::cerr << "Mach::GL ERROR: " << error << std::endl;
    }

    static void MACH_WARN_MSG(const std::string& error) {
        std::cerr << "Mach::GL WARNING: " << error << std::endl;
    }

    static void MACH_MSG(const std::string& msg) {
        std::cout << "Mach::GL: " << msg << std::endl;
    }

    static void MACH_OPEN_GL_MSG(const std::string& msg) {
        std::cout << "Mach::GL: OpenGL: " << msg << std::endl;
    }

    static void MACH_OPEN_AL_MSG(const std::string& msg) {
        std::cout << "Mach::GL: OpenAL: " << msg << std::endl;
    }

    static void MACH_VULKAN_MSG(const std::string& msg) {
        std::cout << "Mach::GL: Vulkan: " << msg << std::endl;
    }

    struct CachedInstance {

        CachedInstance() = default;
        CachedInstance(const uint32_t& address) { cacheAddress = address; }

        uint32_t cacheAddress = 0;
    };

    static std::string vulkanPackedToString(const uint32_t& packed) {

        std::string result;
        
        uint32_t major = VK_API_VERSION_MAJOR(packed);
        uint32_t minor = VK_API_VERSION_MINOR(packed);
        uint32_t patch = VK_API_VERSION_PATCH(packed);

        result = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);

        return result;
    }

    static size_t read(void* buffer, size_t elementSize, size_t elementCount, void* dataSource) {
        assert(elementSize == 1);

        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        stream.read(static_cast<char*>(buffer), elementCount);
        const std::streamsize bytesRead = stream.gcount();
        stream.clear();
        return static_cast<size_t>(bytesRead);
    }

    static int seek(void* dataSource, ogg_int64_t offset, int origin) {
        static const std::vector<std::ios_base::seekdir> seekDirections{
            std::ios_base::beg, std::ios_base::cur, std::ios_base::end
        };

        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        stream.seekg(offset, seekDirections.at(origin));
        stream.clear();
        return 0;
    }

    static long tell(void* dataSource) {
        std::ifstream& stream = *static_cast<std::ifstream*>(dataSource);
        const auto position = stream.tellg();
        assert(position >= 0);
        return static_cast<long>(position);
    }
}

//Fix compatability issues with YAML and custom data structures
namespace YAML {

    template<>
    struct convert<float2> {

        static Node encode(const float2& rhs) {

            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, float2& rhs) {

            if (!node.IsSequence() || node.size() != 2) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<float3> {

        static Node encode(const float3& rhs) {

            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, float3& rhs) {

            if (!node.IsSequence() || node.size() != 3) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<float4> {

        static Node encode(const float4& rhs) {

            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, float4& rhs) {

            if (!node.IsSequence() || node.size() != 4) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}
