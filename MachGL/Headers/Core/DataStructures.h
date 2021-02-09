#pragma once

#include "Includes.h"

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
    unsigned int color;
    float shine;
    float reflectivity;
    float textureScale;
};

struct Index {

    GLushort index;
};

namespace MachGL {

    template<typename T> using uPoint = std::unique_ptr<T>;

    template<typename T, typename ... Args> constexpr uPoint<T> make_uPoint(Args&& ... args) {

        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T> using sPoint = std::shared_ptr<T>;

    template<typename T, typename ... Args> constexpr sPoint<T> make_sPoint(Args&& ... args) {

        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
