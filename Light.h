#pragma once

#include "Includes.h"
#include "DataStructures.h"

namespace MachGL {
    namespace Object {

        class Light {

        private:
            float3 m_position;
            float4 m_color;
            float3 m_attenuation = float3(1, 0, 0);
            float m_brightness = 1.0f;

        public:
            Light(const float3& position, const float4& color) : m_position(position), m_color(color) { }
            ~Light() = default;

            inline void setPosition(const float3& pos) { m_position = pos; }
            inline void setColor(const float4& color) { m_color = color; }
            inline void setAttenuation(const float3& attenuation) { m_attenuation = attenuation; }
            inline void setBrightness(const float& brightness) { m_brightness = brightness; }
            inline const float3& getPosition() const { return m_position; }
            inline const float4& getColor() const { return m_color; }
            inline const float3& getAttenuation() const { return m_attenuation; }
            inline const float& getBrightness() const { return m_brightness; }
        };
    }
}