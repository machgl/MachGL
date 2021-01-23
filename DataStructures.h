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