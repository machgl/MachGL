/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Maths {

		class Vector {

			public:

				//2D Vectors

				static float dotProduct(const float2& v1, const float2& v2) {
					return glm::dot(v1, v2);
				}

				static float length(const float2& v) {
					return sqrtf(dotProduct(v, v));
				}

				static float2 normalize(const float2& v) {
					return glm::normalize(v);
				}

				static void printVector(const float2& v) {
					std::cout << "x: " << v.x << ", y: " << v.y << std::endl;
				}

                static float distance(const float2& v1, const float2& v2) {
                    return glm::distance(v1, v2);
                }

                //3D Vectors

                static float dotProduct(const float3& v1, const float3& v2) {
                    return glm::dot(v1, v2);
                }

                static float3 crossProduct(const float3& v1, const float3& v2) {
					return glm::cross(v1, v2);
                }

                static float length(const float3& v) {
                    return sqrtf(dotProduct(v, v));
                }

                static float3 normalize(const float3& v) {
					return glm::normalize(v);
                }

                static void printVector(const float3& v) {
                    std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << std::endl;
                }

                static float distance(const float3& v1, const float3& v2) {
                    return glm::distance(v1, v2);
                }

                // 4D Vectors

                static float dotProduct(const float4& v1, const float4& v2) {
                    return glm::dot(v1, v2);
                }

                static float length(const float4& v) {
                    return sqrtf(dotProduct(v, v));
                }

                static float4 normalize(const float4& v) {
                    return glm::normalize(v);
                }

                static void printVector(const float4& v) {
                    std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w << std::endl;
                }

                static float distance(const float4& v1, const float4& v2) {
                    return glm::distance(v1, v2);
                }
		};
	}

}
