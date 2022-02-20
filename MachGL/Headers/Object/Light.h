#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
    namespace Object {

        struct LightProperties {

            float4 color = float4(0);
            float4 position = float4(0);
            float4 attenuation = float4(1, 0, 0, 1);
            float4 brightness = float4(0);
        };

        static LightProperties defaultLightProperties;

        class Light {

        private:
            float3 m_position;
            float4 m_color;
            LightProperties m_properties;

        public:
            Light(const float3& position, const float4& color) : m_position(position), m_color(color) { 
                
                m_properties.color = m_color;
                m_properties.position = float4(m_position, 0);
            }
            ~Light() = default;

            inline void setPosition(const float3& pos) { m_position = pos; }
            inline void setColor(const float4& color) { m_color = color; }
            inline void setAttenuation(const float4& attenuation) { m_properties.attenuation = attenuation; }
            inline void setBrightness(const float& brightness) { m_properties.brightness = float4(brightness); }
            inline const float3& getPosition() const { return m_position; }
            inline const float4& getColor() const { return m_color; }
            inline const float3& getAttenuation() const { return m_properties.attenuation; }
            inline const float& getBrightness() const { return m_properties.brightness.x; }
            inline const LightProperties& getProperties() { return m_properties; }
        };
    }
}