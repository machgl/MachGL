/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "Image.h"
#include "Shader.h"

namespace MachGL {
    namespace Graphics {

        class Sprite {
            
            public:
                float2 m_position;
                float2 m_size;
                MACH_IMAGE m_texture;
                float4 m_color;
                matrix4x4 m_translationMatrix;
                
            public:
                Sprite(const float2& position, const float2& size, const MACH_IMAGE& texture, const float4& color = float4(0));
                void translate(const matrix4x4& translationMatrix);
        };

        class BatchRenderer {
            
            protected:
                const static uint32_t m_maxQuads = 10000;
                MACH_SHADER m_shader;
                std::vector<Sprite> m_sprites;
                uint32_t m_vertexSize = sizeof(Vertex);
                uint32_t m_indexSize = sizeof(Index);
                uint32_t m_quadVertexSize = m_vertexSize * 4;
                uint32_t m_quadIndexSize = m_indexSize * 6;
                uint32_t m_vertexBufferSize = m_maxQuads * m_quadVertexSize;
                uint32_t m_indexBufferSize = m_maxQuads * m_quadIndexSize;
                uint32_t m_indices[m_maxQuads * 6];
            
                std::vector<float3> m_quadVertices = {

                    float3(0, 0, 0),
                    float3(0, 1, 0),
                    float3(1, 1, 0),
                    float3(1, 0, 0)
                };

                std::vector<unsigned short> m_quadIndices = {

                    0, 1, 2, 2, 3, 0
                };

                std::vector<float2> m_quadUVs = {

                    float2(0, 1),
                    float2(0, 0),
                    float2(1, 0),
                    float2(1, 1)
                };
            
            
            public:
                static sPoint<BatchRenderer> createBatchRenderer();
                BatchRenderer() = default;
                ~BatchRenderer() = default;
                void submit(const std::vector<Sprite>& sprites);
                void setShader(const MACH_SHADER& shader);
                virtual void destroy() = 0;
            protected:
                virtual void begin() = 0;
                virtual void push() = 0;
                virtual void end() = 0;
                virtual void flush() = 0;
        };
    
        using MACH_BATCH_RENDERER = sPoint<BatchRenderer>;
    }
}
